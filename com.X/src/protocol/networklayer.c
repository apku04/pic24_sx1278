/*  ============================================================================
    Copyright (C) 2015 Achuthan Paramanathan.
    ============================================================================
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
    ============================================================================
    Revision Information:
        File name: opm.c
        Version:   v0.0
        Date:      23-07-2015
    ============================================================================
 */

/*
 ** ============================================================================
 **                        INCLUDE STATEMENTS
 ** ============================================================================
 */


#include <string.h>
#include <stdlib.h>
#include "networklayer.h"
#include "maclayer.h"
#include "ringBuffer.h"

/*
 ** ============================================================================
 **                   LOCAL  FUNCTION DECLARATIONS
 ** ============================================================================
 */

GLOB_RET network_outgoing( uint8_t addr, uint8_t len, void *frame );
GLOB_RET network_incoming( void *frame, uint8_t len);
char find_next_hop(void);

/*
** ==========================================================================
**                       Layer specific variables
** ==========================================================================
*/

nlme Nlme;


/*
** =============================================================================
**                    FUNCTIONS
** =============================================================================
*/

/*==============================================================================
** Function...: opmInit
** Return.....: GLOB_RET
** Description: network layer initialization
** Created....: 29.12.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void opmInit(void)
{
    Nlme.ttl = 7;
    Nlme.headerSize = 4;
    Nlme.networkSize = 20;

}

/*==============================================================================
** Function...: network_layer
** Return.....: GLOB_RET
** Description: network layer interface. All call must go thoug this interface
** Created....: 04.04.2013 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET network_interface(Direction iKey, uint8_t addr, uint8_t len, void *frame)
{
    GLOB_RET ret = GLOB_SUCCESS;

    if (OUTGOING == iKey)
    {
        ret = network_outgoing(addr, len, frame);
        if (ret != GLOB_SUCCESS) {
            return GLOB_ERROR_NETWORK_OUTGOING_FAILED;
        }
    }
    else if (INCOMING == iKey)
    {
        ret = network_incoming(frame, len);
        if (ret != GLOB_SUCCESS) {
            return GLOB_ERROR_NETWORK_INCOMING_FAILED;
        }
    }
    else
    {
        return GLOB_ERROR_UNKNOWN_DIRECTION;
    }
    return ret;
}


/*==============================================================================
** Function...: network_outgoing
** Return.....: GLOB_RET
** Description: private function that handles all outgoing packets
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET network_outgoing(uint8_t addr, uint8_t len, void *frame)
{
    GLOB_RET ret = GLOB_SUCCESS;

    uint8_t netFrame[64]; // Set a suitable size based on your application requirements
    uint8_t netFrameSize = len + Nlme.headerSize;
    uint8_t con = 0, rsv = 0, nextDest = 0;

    if (netFrameSize > sizeof(netFrame)) {
        return GLOB_ERROR_MEMORY_ALLOCATION;
    }

    memcpy(netFrame, &Nlme.ttl, 1); // TTL
    memcpy(netFrame + 1, &addr, 1); // mesh dest
    memcpy(netFrame + 2, &con, 1);  // con
    memcpy(netFrame + 3, &rsv, 1);  // rsv

    memcpy(netFrame + 4, frame, len);

    //op_hexdump(1, "----- NET LAYER ----", netFrame, netFrameSize, true);

    // Add MAC / MESH header
    nextDest = find_next_hop();

    mac_interface(OUTGOING, addr, netFrameSize, netFrame);

    return ret;
}



/*==============================================================================
** Function...: network_incoming
** Return.....: GLOB_RET
** Description: private function that handles all incomming packets
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET network_incoming( void *frame, uint8_t len)
{
    GLOB_RET ret = GLOB_SUCCESS;
    
    uint8_t netFrame[64];
    memcpy(netFrame, frame, len);  
    
    if(GLOB_ERROR_BUFFER_FULL != buffer_full(&rxBuf)) {
        write_buffer(&netFrame[4], &rxBuf);
    }
    
    return ret;
}


/*==============================================================================
** Function...: find_next_hop
** Return.....: char
** Description: private function that find the next hop.
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
char find_next_hop(void)
{

    return 255;
    
}