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

#include "maclayer.h"
#include "../../mcc_generated_files/ext_int.h"

static GLOB_RET mac_outgoing(Packet *pkt);
static GLOB_RET mac_incoming( Packet *pkt );
static void aloha_channel_access(Packet *pkt);

mlme Mlme;

#define MAX_WAIT_TIME 1000  // Maximum random wait time in ms

/*
** =============================================================================
**                  PRIVATE FUNCTIONS
** =============================================================================
*/

static void aloha_channel_access(Packet *pkt) {
    uint16_t di = (rand() % 10 + 2); 
    delay_ms(di * 20); 
    
    uint8_t isChannelBusy = sx1278_get_carrier_detect_average();
        
    // If channel is busy, wait for a random period and retry
    while (isChannelBusy >= 1) {
        LED_B = 1;
        uint16_t d = (rand() % 10 + 2); 
        // Delay for waitTime
        delay_ms(d * 200); 
        // Check channel status again
        isChannelBusy = sx1278_get_carrier_detect_average();
    }
    LED_B = 0;
    // If channel is not busy, transmit the frame
    transmitFrame(pkt);
}

static GLOB_RET mac_incoming( Packet *pkt )
{
    // Copy the meta data from rx frame to pass on to the next layer
     
    if(pkt->source_adr != Mlme.mAddr)
    {
        if ( (BROADCAST == pkt->destination_adr) || 
             (Mlme.mAddr == pkt->destination_adr) ||
             (0 == pkt->destination_adr)   
            ) {

            pkt->pOwner = NET;
            pkt->pktDir = INCOMING;
            if(GLOB_ERROR_BUFFER_FULL != buffer_full(Mlme.pktRxBuf)) {

                write_packet(Mlme.pktRxBuf, pkt);
            }
        }
    }
    GLOB_RET ret = GLOB_SUCCESS; 
    return ret;
}

static GLOB_RET mac_outgoing(Packet *pkt)
{
    GLOB_RET ret = GLOB_SUCCESS;
    
    if( pkt->pktDir == OUTGOING)
    {
        pkt->length = pkt->length + Mlme.headerSize;
        pkt->source_adr = Mlme.mAddr;
        pkt->control_mac = 0;
        pkt->protocol_Ver = 10;
    }
    
    if (255 == pkt->destination_adr) {
        Mlme.mBcast = YES;
    } else {
        Mlme.mBcast = NO;
    }
    aloha_channel_access(pkt);
    
    return ret;
}

/*
** =============================================================================
**                  PUBLIC FUNCTIONS
** =============================================================================
*/

GLOB_RET set_mac_address(uint8_t addr) {
    if (addr < 1 || addr > 254) {
        return GLOB_ERROR_OUT_OF_RANGE_PARAM;
    }
    Mlme.mAddr = addr;
    return GLOB_SUCCESS;
}

uint8_t get_mac_address(void) {
    return Mlme.mAddr;
}

void mac_layer_init(PacketBuffer *pRxBuf, PacketBuffer *pTxBuf) 
{
    Mlme.pktRxBuf = pRxBuf;
    Mlme.pktTxBuf = pTxBuf;
    Mlme.headerSize = MAC_HEADER_SIZE;
    Mlme.mAddr = 2;
    srand(4125);
}

GLOB_RET mac_interface(char iKey) {
    GLOB_RET ret = GLOB_SUCCESS;

    if (OUTGOING == iKey || RETX == iKey) {
        Packet pkt = search_pending_packet(Mlme.pktTxBuf, iKey, MAC);

        if (pkt.pktDir != DIR_EMPTY && pkt.pOwner != OWNER_EMPTY) {
            ret = mac_outgoing(&pkt);
        }
    } else if (INCOMING == iKey) {
        Packet pkt = search_pending_packet(Mlme.pktRxBuf, iKey, MAC);
        if (pkt.pktDir != DIR_EMPTY && pkt.pOwner != OWNER_EMPTY) {
            ret = mac_incoming(&pkt);
        }
    } else {
        ret = GLOB_ERROR_INVALID_PARAM;
    }
    
    return ret;
}