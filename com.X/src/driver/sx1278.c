/* ============================================================================
Copyright (C) 2015 Achuthan Paramanathan.
===============================================================================
This program is distributed under the terms of the GNU General Public License.
For details, see <http://www.gnu.org/licenses/>.
===============================================================================
Revision Information:
File name: zeus.c
Version:   v0.0
Date:      31-10-2019
=============================================================================== 
 */

/*
** =============================================================================
**                        INCLUDE STATEMENTS
** =============================================================================
*/
#include <stdio.h>
#include "xc.h"
#include "main.h"
#include "sx1278.h"
#include "timerdriver.h"
#include "usbdriver.h"
#include "sx1278_register.h"
#include "maclayer.h"
#include "packetBuffer.h"

/*
** =============================================================================
**                           LOCAL DEFINES
** =============================================================================
*/
#define RSSI_THRESHOLD -100

/*
** =============================================================================
**                   LOCAL FUNCTION DECLARATIONS
** =============================================================================
*/
static void receive_packet(void);
static void reset_radio(void);
static void set_mode_sleep(void);
static void set_mode_idle(void);
static void set_mode_tx(void);
static void set_mode_lora(void);
static uint8_t read_register(uint8_t addr);
static void write_register(uint8_t addr, uint8_t value);
static void write_burst_register(uint8_t adr, uint8_t* data, uint8_t len);
static void set_mode_rx(void);
static void wait_packet_sent( void );
static uint8_t sx1278_get_carrier_detect(void);

/*
** =============================================================================
**                       LOCAL VARIABLES
** =============================================================================
*/
static PacketBuffer *pktRxBuf;
static PacketBuffer *pktTxBuf;

static uint8_t tx_done_irq = 0;

// The Frequency Synthesizer step = RH_RF95_FXOSC / 2^^19
#define RH_RF95_FSTEP  (RH_RF95_FXOSC / 524288)

// The crystal oscillator frequency of the module
#define RH_RF95_FXOSC 32000000.0

#define RSSI_LF -164
#define RSSI_HF -157



/*
** =============================================================================
**                       PRIVATE FUNCTIONS
** =============================================================================
*/

static uint8_t sx1278_get_carrier_detect(void) {
    int16_t rssi = read_register(0x1B);
    rssi = RSSI_LF + rssi;
    
    if (rssi > RSSI_THRESHOLD) {
        return 1;  // Carrier detected
    }
    
    return 0;  // No carrier detected
}

static void reset_radio(void)
{
    RESET = 1;
    delay_ms(150);
    RESET = 0;
    delay_ms(150);
    RESET = 1;
    delay_ms(150);
}

static uint8_t read_register(uint8_t addr)
{
    uint8_t spibuf[2];
    spibuf[0] = addr & 0x7F;
    spibuf[1] = 0x00;
    SPICSN = 0;
    SPI1_Exchange8bitBuffer(spibuf , 2,  spibuf);
    SPICSN = 1;
    return spibuf[1];
}

static void write_register(uint8_t addr, uint8_t value)
{
    uint8_t spibuf[2];
    spibuf[0] = addr | 0x80;
    spibuf[1] = value;
    SPICSN = 0;
    SPI1_Exchange8bitBuffer(spibuf , 2,  spibuf);
    SPICSN = 1;
}

static void write_burst_register(uint8_t adr, uint8_t* data, uint8_t len)
{
    uint8_t i = 0;

    for(i=0;i<len;i++)
    {
        write_register(adr, data[i]);
    }

}

static void set_mode_rx(void)
{
    //set tx mode
    uint8_t value = read_register(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_RXCONTINUOUS & 0x07);
    write_register(RF95_REG_01_OP_MODE, value);
    
}

static void set_mode_tx(void)
{
    //set tx mode
    uint8_t value = read_register(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_TX & 0x07);
    write_register(RF95_REG_01_OP_MODE, value);
    
}

static void set_mode_idle(void)
{
    uint8_t value = read_register(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_STDBY & 0x07);
    write_register(RF95_REG_01_OP_MODE, value);
}

static void set_mode_sleep(void)
{
    uint8_t value = read_register(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_SLEEP & 0x07);
    write_register(RF95_REG_01_OP_MODE, value);
}

static void set_mode_lora(void)
{
    uint8_t value = read_register(RF95_REG_01_OP_MODE);
    value = (value & ~0x80) | (RF95_LONG_RANGE_MODE & 0x80);
    write_register(RF95_REG_01_OP_MODE, value);
}

static void wait_packet_sent( void )
{
    while(!tx_done_irq);
}

static void receive_packet(void) {
    int16_t SNR;
    uint8_t payload[BUFFER_DATA_SIZE];
    int i = 0;


    uint8_t value = read_register(RF95_REG_19_PKT_SNR_VALUE);
    SNR = (value & 0x80) ? -(int16_t)((~value + 1) >> 2) : (int16_t)(value >> 2);

    int irqflags = read_register(RF95_REG_12_IRQ_FLAGS);
    write_register(RF95_REG_12_IRQ_FLAGS, RF95_RX_DONE);

    if (irqflags & RF95_PAYLOAD_CRC_ERROR) {
        print("CRC error\n\r");
        write_register(RF95_REG_12_IRQ_FLAGS, RF95_PAYLOAD_CRC_ERROR);
    } else {
        
        Packet pkt;

        
        uint8_t currentAddr = read_register(RF95_REG_10_FIFO_RX_CURRENT_ADDR);
        uint8_t receivedCount = read_register(RF95_REG_13_RX_NB_BYTES);
        memset(payload, 0, BUFFER_DATA_SIZE);
        write_register(RF95_REG_0D_FIFO_ADDR_PTR, currentAddr);

        int16_t rssi = RSSI_LF + read_register(0x1B);
        int16_t prssi = RSSI_LF + read_register(0x1A);

        payload[2] = receivedCount;
        
        for (i = 0; i < receivedCount; i++) {
            payload[i+3] = (char)read_register(RF95_REG_00_FIFO);
        }
        
        pkt.pktDir = INCOMING;
        pkt.pOwner = MAC;
        
        pkt.rssi = rssi;
        pkt.prssi = prssi;
        pkt.rxCnt = payload[2];
        pkt.destination_adr = payload[3];
        pkt.source_adr = payload[4];
        pkt.sequence_num = (payload[6] << 8) | payload[5];
        pkt.control_mac = payload[7];
        pkt.protocol_Ver = payload[8];
        pkt.TTL = payload[9];
        pkt.mesh_dest = payload[10];
        pkt.mesh_tbl_entries = payload[11];
        pkt.mesh_src = payload[12];
        pkt.control_app = payload[13];
        pkt.length = payload[14];
        
        uint8_t data_size = pkt.length-PACKET_HEADER_SIZE;
        if (data_size < 50) // we dont want mem overflow
        {
            memcpy(pkt.data, &payload[15], data_size);
            if(GLOB_ERROR_BUFFER_FULL != buffer_full(pktRxBuf)) {
                write_packet(pktRxBuf, &pkt);
            }
        }
        
    }
}

/*
** =============================================================================
**                       PUBLIC FUNCTIONS
** =============================================================================
*/

void radio_irq_handler(void) {
    uint8_t irqflags = read_register(RF95_REG_12_IRQ_FLAGS);

    if (irqflags & RF95_RX_DONE) {
        receive_packet();
    } else if (irqflags & RF95_TX_DONE) {
        tx_done_irq = 1;
    } else if (irqflags & RF95_CAD_DETECTED) {
        // Handle CAD detected event if needed
    }
}

uint8_t initiate_receiver(void) {
    if (!SLME.radio_initialized) {
        print("ERROR! Initiate receiver\n\r");
        SLME.receiver_initialized = FALSE;
        return 1;
    }

    // Configure DIO mapping: DIO0=RxDone, DIO1=RxTout, DIO2=NOP
    write_register(RF95_REG_40_DIO_MAPPING1, RF95_MAP_DIO0_LORA_RXDONE |
                                            RF95_MAP_DIO1_LORA_RXTOUT |
                                            RF95_MAP_DIO2_LORA_NOP);
    // Clear all radio IRQ flags
    write_register(RF95_REG_12_IRQ_FLAGS, 0xFF);
    // Mask all IRQs but RxDone
    write_register(RF95_REG_11_IRQ_FLAGS_MASK, ~RF95_RX_DONE_MASK);

    set_mode_rx();
    SLME.receiver_initialized = TRUE;

    return 0;
}

uint8_t initiate_sender(void) {
    if (!SLME.radio_initialized) {
        print("ERROR! Initiate sender\n\r");
        SLME.sender_initialized = FALSE;
        return 1;
    }

    // Set the IRQ mapping: DIO0=TxDone, DIO1=NOP, DIO2=NOP
    write_register(RF95_REG_40_DIO_MAPPING1, RF95_TX_DONE |
                                            RF95_MAP_DIO1_LORA_NOP |
                                            RF95_MAP_DIO2_LORA_NOP);
    // Clear all radio IRQ flags
    write_register(RF95_REG_12_IRQ_FLAGS, 0xFF);
    // Mask all IRQs but TxDone
    write_register(RF95_REG_11_IRQ_FLAGS_MASK, ~RF95_TX_DONE_MASK);

    SLME.sender_initialized = TRUE;

    return 0;
}

uint8_t send(uint8_t *payload, uint8_t length)
{
    initiate_sender();

    write_register(RF95_REG_0E_FIFO_TX_BASE_ADDR, 0x00);
    write_register(RF95_REG_0D_FIFO_ADDR_PTR, 0x00);
    
    // The message data
    write_burst_register(RF95_REG_00_FIFO, payload, length);
    write_register(RF95_REG_22_PAYLOAD_LENGTH, length);
    
    set_mode_tx();
    wait_packet_sent(); 
    
    LED_A_TOGGLE;
    
    initiate_receiver();

    return 0;
}

uint8_t setup_lora(PacketBuffer *pRxBuf, PacketBuffer *pTxBuf)
{
    
    if( pRxBuf == NULL || pTxBuf == NULL)
    {
        print("Error invalid buffer initialization");
        return 1;
    }
    
    pktRxBuf = pRxBuf;
    pktTxBuf = pTxBuf;
    
    reset_radio();
    
    set_mode_sleep();
    set_mode_lora();
    
    delay_ms(10);
        
    if( read_register(RF95_REG_01_OP_MODE) != ( RF95_MODE_SLEEP | 
                                               RF95_LONG_RANGE_MODE | 
                                               RF95_MODE_LF )  )
    {
        print("ERROR! not in sleep mode\n\r");
        SLME.radio_initialized = FALSE;
    }
    
    // Set up FIFO
    // Configure the entire 256 bytes of the FIFO for both receive and transmit,
    // not both at the same time
    write_register(RF95_REG_0E_FIFO_TX_BASE_ADDR, 0);
    write_register(RF95_REG_0F_FIFO_RX_BASE_ADDR, 0);
    
    set_mode_idle();
    delay_ms(10);
    
    // Using  Explicit Header mode, CR 4/5, bw 125 kHz
    write_register(RF95_REG_1D_MODEM_CONFIG1,       0x72);
    // CRC disabled, single packet send mode, SF 7
    write_register(RF95_REG_1E_MODEM_CONFIG2,       0x76);
    //  LNA gain set by the internal AGC loop, LowDataRateOptimize disabled
    write_register(RF95_REG_26_MODEM_CONFIG3,       0x04);
    
    //setPreambleLength,  Default is 8
    write_register(RF95_REG_20_PREAMBLE_MSB, 8 >> 8);
    write_register(RF95_REG_21_PREAMBLE_LSB, 8 & 0xff);
    
    // set frequency
    uint32_t frf = (868 * 1000000.0) / RH_RF95_FSTEP;
    write_register(RF95_REG_06_FRF_MSB, (uint8_t)(frf>>16) );
    write_register(RF95_REG_07_FRF_MID, (uint8_t)(frf>> 8) );
    write_register(RF95_REG_08_FRF_LSB, (uint8_t)(frf>> 0) );
    
    //set power to 14
    write_register(RF95_REG_09_PA_CONFIG, RF95_PA_SELECT | (14));
    write_register(LORA_REG_SYNCWORD, 0x12);
    

    write_register(RF95_REG_0C_LNA, RF95_LNA_MAX_GAIN);  // max lna gain
    // set max payload size
    write_register(RF95_REG_23_MAX_PAYLOAD_LENGTH, 64);
    
    SLME.radio_initialized = TRUE;
    
    return 0;
}

void print_all_registers(void)
{
    uint8_t value = 0x0;
    uint8_t i = 0;
    char s[20];
    
    for(i=0; i<127; i++)
    {
        value = read_register(i);
        sprintf(s,"0x%02X 0x%02X\n\r", i, value);
        print(s);
        delay_ms(100);
    }
}

uint8_t sx1278_set_channel(uint32_t freq) {

    set_mode_idle();
    
    uint32_t frf = (uint32_t)((double)freq / RH_RF95_FSTEP);
    write_register(RF95_REG_06_FRF_MSB, (uint8_t)(frf >> 16));
    write_register(RF95_REG_07_FRF_MID, (uint8_t)(frf >> 8));
    write_register(RF95_REG_08_FRF_LSB, (uint8_t)(frf));
    
    return initiate_receiver();
}

uint32_t sx1278_get_channel(void) {
    uint32_t frf = ((uint32_t)read_register(RF95_REG_06_FRF_MSB) << 16) |
                   ((uint32_t)read_register(RF95_REG_07_FRF_MID) << 8) |
                   (uint32_t)read_register(RF95_REG_08_FRF_LSB);
    uint32_t freq = (uint32_t)((double)frf * RH_RF95_FSTEP);
    return freq;
}

void sx1278_set_datarate(uint8_t data_rate) {
    uint8_t config2 = read_register(RF95_REG_1E_MODEM_CONFIG2);
    config2 = (config2 & 0x0F) | ((data_rate & 0x0F) << 4);
    write_register(RF95_REG_1E_MODEM_CONFIG2, config2);
}

uint8_t sx1278_get_datarate(void) {
    uint8_t config2 = read_register(RF95_REG_1E_MODEM_CONFIG2);
    uint8_t data_rate = (config2 >> 4) & 0x0F;
    return data_rate;
}

void sx1278_set_tx_power(uint8_t power) {
    uint8_t pa_config = read_register(RF95_REG_09_PA_CONFIG);
    pa_config = (pa_config & 0xF0) | (power & 0x0F);
    write_register(RF95_REG_09_PA_CONFIG, pa_config);
}

uint8_t sx1278_get_tx_power(void) {
    uint8_t pa_config = read_register(RF95_REG_09_PA_CONFIG);
    uint8_t power = pa_config & 0x0F;
    return power;
}

uint8_t sx1278_get_carrier_detect_average(void) {
    int16_t totalRssi = 0;
    for (int i = 0; i < 10; i++) {
        totalRssi += sx1278_get_carrier_detect();
        delay_ms(1);  // Wait for 1ms between samples
    }
    
    // Calculate average
    uint8_t averageRssi = totalRssi / 10;
    
    return averageRssi;
}