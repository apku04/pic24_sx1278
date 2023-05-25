/*  ============================================================================
Copyright (C) 2015 Achuthan Paramanathan.
================================================================================
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
================================================================================
Revision Information:
File name: zeus.c
Version:   v0.0
Date:      31-10-2019
================================================================================
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
#include "ringBuffer.h"
#include "globalInclude.h"
#include "maclayer.h"

/*
** =============================================================================
**                           LOCAL DEFINES
** =============================================================================
*/


/*
** =============================================================================
**                   LOCAL FUNCTION DECLARATIONS
** =============================================================================
*/
void resetRadio(void);
void setModeSleep(void);
void setModeIdle(void);
void setModeTx(void);
void setModeLoRa(void);
uint8_t readRegister(uint8_t addr);
void writeRegister(uint8_t addr, uint8_t value);
void writeBurstRegister(uint8_t adr, uint8_t* data, uint8_t len);
uint8_t receivePkt(uint8_t *payload);
void setModeRx(void);

/*
** =============================================================================
**                       LOCAL VARIABLES
** =============================================================================
*/

static uint8_t tx_done_irq = 0;


// The Frequency Synthesizer step = RH_RF95_FXOSC / 2^^19
#define RH_RF95_FSTEP  (RH_RF95_FXOSC / 524288)

// The crystal oscillator frequency of the module
#define RH_RF95_FXOSC 32000000.0

// The length of the header.
// The headers are inside the LORA's payload


void waitPacketSent( void )
{
    while(!tx_done_irq);
}


/*==============================================================================
** Function...: receive_packet
** Return.....: void
** Description: Receive the packet.
** Created....: 1.03.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void receive_packet(void) {
    int16_t SNR;
    uint8_t payload[BUFFER_DATA_SIZE];
    int i = 0;


    uint8_t value = readRegister(RF95_REG_19_PKT_SNR_VALUE);
    SNR = (value & 0x80) ? -(int16_t)((~value + 1) >> 2) : (int16_t)(value >> 2);

    int irqflags = readRegister(RF95_REG_12_IRQ_FLAGS);
    writeRegister(RF95_REG_12_IRQ_FLAGS, RF95_RX_DONE);

    if (irqflags & RF95_PAYLOAD_CRC_ERROR) {
        usb_print("CRC error\n\r");
        writeRegister(RF95_REG_12_IRQ_FLAGS, RF95_PAYLOAD_CRC_ERROR);
    } else {
        uint8_t currentAddr = readRegister(RF95_REG_10_FIFO_RX_CURRENT_ADDR);
        uint8_t receivedCount = readRegister(RF95_REG_13_RX_NB_BYTES);

        writeRegister(RF95_REG_0D_FIFO_ADDR_PTR, currentAddr);

        int16_t rssi = readRegister(0x1B);
        int16_t prssi = readRegister(0x1A);

        memset(payload, 0, BUFFER_DATA_SIZE);

        payload[0] = rssi;
        payload[1] = prssi;
        payload[2] = receivedCount;

        for (i = 0; i < receivedCount; i++) {
            payload[i + 3] = (char)readRegister(RF95_REG_00_FIFO);
        }
        LED_GREEN_1_TOGGLE;
        mac_interface(INCOMING, 0, i+3, payload);
    }
    
}

/*==============================================================================
** Function...: radio_irq_handler
** Return.....: void
** Description: Handles the incoming IRQ. Called from ext int.
** Created....: 1.03.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void radio_irq_handler(void) {
    uint8_t irqflags = readRegister(RF95_REG_12_IRQ_FLAGS);

    if (irqflags & RF95_RX_DONE) {
        receive_packet();
    } else if (irqflags & RF95_TX_DONE) {
        tx_done_irq = 1;
    } else if (irqflags & RF95_CAD_DETECTED) {
        // Handle CAD detected event if needed
    }
}



/*==============================================================================
** Function...: initiate_receiver
** Return.....: uint8_t
** Description: Initiate the receiver
** Created....: 29.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint8_t initiate_receiver(void) {
    if (!SLME.radio_initialized) {
        usb_print("ERROR! Initiate receiver\n\r");
        SLME.receiver_initialized = FALSE;
        return 1;
    }

    // Configure DIO mapping: DIO0=RxDone, DIO1=RxTout, DIO2=NOP
    writeRegister(RF95_REG_40_DIO_MAPPING1, RF95_MAP_DIO0_LORA_RXDONE |
                                            RF95_MAP_DIO1_LORA_RXTOUT |
                                            RF95_MAP_DIO2_LORA_NOP);
    // Clear all radio IRQ flags
    writeRegister(RF95_REG_12_IRQ_FLAGS, 0xFF);
    // Mask all IRQs but RxDone
    writeRegister(RF95_REG_11_IRQ_FLAGS_MASK, ~RF95_RX_DONE_MASK);

    setModeRx();
    SLME.receiver_initialized = TRUE;

    return 0;
}

/*==============================================================================
** Function...: initiate_sender
** Return.....: uint8_t
** Description: Initiate the Sender
** Created....: 29.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint8_t initiate_sender(void) {
    if (!SLME.radio_initialized) {
        usb_print("ERROR! Initiate sender\n\r");
        SLME.sender_initialized = FALSE;
        return 1;
    }

    // Set the IRQ mapping: DIO0=TxDone, DIO1=NOP, DIO2=NOP
    writeRegister(RF95_REG_40_DIO_MAPPING1, RF95_TX_DONE |
                                            RF95_MAP_DIO1_LORA_NOP |
                                            RF95_MAP_DIO2_LORA_NOP);
    // Clear all radio IRQ flags
    writeRegister(RF95_REG_12_IRQ_FLAGS, 0xFF);
    // Mask all IRQs but TxDone
    writeRegister(RF95_REG_11_IRQ_FLAGS_MASK, ~RF95_TX_DONE_MASK);

    SLME.sender_initialized = TRUE;

    return 0;
}


/*==============================================================================
** Function...: send
** Return.....: uint8_t
** Description: Send a packet using sx1278
** Created....: 10.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint8_t send(uint8_t* data, uint8_t len)
{
    if(!SLME.sender_initialized)
    {
        usb_print("ERROR! Send\n\r");
        return 1;
    }
    
    writeRegister(RF95_REG_0E_FIFO_TX_BASE_ADDR, 0x00);
    writeRegister(RF95_REG_0D_FIFO_ADDR_PTR, 0x00);
    
    // The message data
    writeBurstRegister(RF95_REG_00_FIFO, data, len);
    writeRegister(RF95_REG_22_PAYLOAD_LENGTH, len);
    
    setModeTx();
    waitPacketSent(); 

    return 0;
}


/*==============================================================================
** Function...: setupLora
** Return.....: uint8_t
** Description: Setup sx1278 for lora
** Created....: 10.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint8_t setupLora(void)
{
    resetRadio();
    
    setModeSleep();
    setModeLoRa();
    
    delay_ms(10);
        
    if( readRegister(RF95_REG_01_OP_MODE) != ( RF95_MODE_SLEEP | 
                                               RF95_LONG_RANGE_MODE | 
                                               RF95_MODE_LF )  )
    {
        usb_print("ERROR! not in sleep mode\n\r");
        SLME.radio_initialized = FALSE;
    }
    
    // Set up FIFO
    // Configure the entire 256 bytes of the FIFO for both receive and transmit,
    // not both at the same time
    writeRegister(RF95_REG_0E_FIFO_TX_BASE_ADDR, 0);
    writeRegister(RF95_REG_0F_FIFO_RX_BASE_ADDR, 0);
    
    setModeIdle();
    delay_ms(10);
    
    // Using  Explicit Header mode, CR 4/5, bw 125 kHz
    writeRegister(RF95_REG_1D_MODEM_CONFIG1,       0x72);
    // CRC disabled, single packet send mode, SF 7
    writeRegister(RF95_REG_1E_MODEM_CONFIG2,       0x70);
    //  LNA gain set by the internal AGC loop, LowDataRateOptimize disabled
    writeRegister(RF95_REG_26_MODEM_CONFIG3,       0x04);
    
    //setPreambleLength,  Default is 8
    writeRegister(RF95_REG_20_PREAMBLE_MSB, 8 >> 8);
    writeRegister(RF95_REG_21_PREAMBLE_LSB, 8 & 0xff);
    
    // set frequency
    uint32_t frf = (868 * 1000000.0) / RH_RF95_FSTEP;
    writeRegister(RF95_REG_06_FRF_MSB, (uint8_t)(frf>>16) );
    writeRegister(RF95_REG_07_FRF_MID, (uint8_t)(frf>> 8) );
    writeRegister(RF95_REG_08_FRF_LSB, (uint8_t)(frf>> 0) );
    
    //set power to 14
    writeRegister(RF95_REG_09_PA_CONFIG, RF95_PA_SELECT | (14));
    writeRegister(LORA_REG_SYNCWORD, 0x12);
    

    writeRegister(RF95_REG_0C_LNA, RF95_LNA_MAX_GAIN);  // max lna gain
    // set max payload size
    writeRegister(RF95_REG_23_MAX_PAYLOAD_LENGTH, 64);
    
    SLME.radio_initialized = TRUE;
    
    return 0;
}



/*==============================================================================
** Function...: printAllRegisters
** Return.....: void
** Description: For debugging print out all the regs
** Created....: 31.10.2019 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void printAllRegisters(void)
{
    uint8_t value = 0x0;
    uint8_t i = 0;
    char s[20];
    
    for(i=0; i<127; i++)
    {
        value = readRegister(i);
        sprintf(s,"0x%02X 0x%02X\n\r", i, value);
        usb_print(s);
        delay_ms(100);
    }
}


/*==============================================================================
** Function...: resetRadio
** Return.....: void
** Description: Reset the radio
** Created....: 31.10.2019 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void resetRadio(void)
{
    RESET = 1;
    delay_ms(150);
    RESET = 0;
    delay_ms(150);
    RESET = 1;
    delay_ms(150);
}


/*==============================================================================
** Function...: readRegister
** Return.....: uint8_t
** Description: Read the value from an address
** Created....: 31.10.2019 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint8_t readRegister(uint8_t addr)
{
    uint8_t spibuf[2];
    spibuf[0] = addr & 0x7F;
    spibuf[1] = 0x00;
    SPICSN = 0;
    SPI1_Exchange8bitBuffer(spibuf , 2,  spibuf);
    SPICSN = 1;
    return spibuf[1];
}


/*==============================================================================
** Function...: writeRegister
** Return.....: void
** Description: Write a value to an address
** Created....: 31.10.2019 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void writeRegister(uint8_t addr, uint8_t value)
{
    uint8_t spibuf[2];
    spibuf[0] = addr | 0x80;
    spibuf[1] = value;
    SPICSN = 0;
    SPI1_Exchange8bitBuffer(spibuf , 2,  spibuf);
    SPICSN = 1;
}


/*==============================================================================
** Function...: writeBurstRegister
** Return.....: void
** Description: Burst write values with a length to an address
** Created....: 11.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void writeBurstRegister(uint8_t adr, uint8_t* data, uint8_t len)
{
    uint8_t i = 0;

    for(i=0;i<len;i++)
    {
        writeRegister(adr, data[i]);
    }

}

/*==============================================================================
** Function...: setModeRx
** Return.....: void
** Description: Set sx1278 in RX mode
** Created....: 10.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void setModeRx(void)
{
    //set tx mode
    uint8_t value = readRegister(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_RXCONTINUOUS & 0x07);
    writeRegister(RF95_REG_01_OP_MODE, value);
    
}

/*==============================================================================
** Function...: setModeTx
** Return.....: void
** Description: Set sx1278 in TX mode
** Created....: 10.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void setModeTx(void)
{
    //set tx mode
    uint8_t value = readRegister(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_TX & 0x07);
    writeRegister(RF95_REG_01_OP_MODE, value);
    
}

/*==============================================================================
** Function...: setModeIdle
** Return.....: void
** Description: Set sx1278 in idlemode
** Created....: 10.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void setModeIdle(void)
{
    uint8_t value = readRegister(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_STDBY & 0x07);
    writeRegister(RF95_REG_01_OP_MODE, value);
}

/*==============================================================================
** Function...: setModeSleep
** Return.....: void
** Description: Set sx1278 in sleep mode
** Created....: 10.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void setModeSleep(void)
{
    uint8_t value = readRegister(RF95_REG_01_OP_MODE);
    value = (value & ~0x07) | (RF95_MODE_SLEEP & 0x07);
    writeRegister(RF95_REG_01_OP_MODE, value);
}

/*==============================================================================
** Function...: setModeLoRa
** Return.....: void
** Description: Set sx1278 in LoRa mode
** Created....: 10.02.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void setModeLoRa(void)
{
    uint8_t value = readRegister(RF95_REG_01_OP_MODE);
    value = (value & ~0x80) | (RF95_LONG_RANGE_MODE & 0x80);
    writeRegister(RF95_REG_01_OP_MODE, value);
}


uint8_t sx1278_set_channel(uint32_t freq) {

    setModeIdle();
    
    uint32_t frf = (uint32_t)((double)freq / RH_RF95_FSTEP);
    writeRegister(RF95_REG_06_FRF_MSB, (uint8_t)(frf >> 16));
    writeRegister(RF95_REG_07_FRF_MID, (uint8_t)(frf >> 8));
    writeRegister(RF95_REG_08_FRF_LSB, (uint8_t)(frf));
    
    return initiate_receiver();
}

uint32_t sx1278_get_channel(void) {
    uint32_t frf = ((uint32_t)readRegister(RF95_REG_06_FRF_MSB) << 16) |
                   ((uint32_t)readRegister(RF95_REG_07_FRF_MID) << 8) |
                   (uint32_t)readRegister(RF95_REG_08_FRF_LSB);
    uint32_t freq = (uint32_t)((double)frf * RH_RF95_FSTEP);
    return freq;
}

void sx1278_set_datarate(uint8_t data_rate) {
    uint8_t config2 = readRegister(RF95_REG_1E_MODEM_CONFIG2);
    config2 = (config2 & 0x0F) | ((data_rate & 0x0F) << 4);
    writeRegister(RF95_REG_1E_MODEM_CONFIG2, config2);
}

uint8_t sx1278_get_datarate(void) {
    uint8_t config2 = readRegister(RF95_REG_1E_MODEM_CONFIG2);
    uint8_t data_rate = (config2 >> 4) & 0x0F;
    return data_rate;
}

void sx1278_set_tx_power(uint8_t power) {
    uint8_t pa_config = readRegister(RF95_REG_09_PA_CONFIG);
    pa_config = (pa_config & 0xF0) | (power & 0x0F);
    writeRegister(RF95_REG_09_PA_CONFIG, pa_config);
}

uint8_t sx1278_get_tx_power(void) {
    uint8_t pa_config = readRegister(RF95_REG_09_PA_CONFIG);
    uint8_t power = pa_config & 0x0F;
    return power;
}
