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
        File name: dcf.h
        Version:   v0.0
        Date:      2012-08-09
    ============================================================================
 */

/*
** ==========================================================================
**                        INCLUDE STATEMENTS
** ==========================================================================
*/

#ifndef DCF_H
#define	DCF_H

#include <stdlib.h> 
#include <math.h>

#include "globalInclude.h"
#include "sx1278.h"
#include "hal.h"
#include "maclayer_defs.h"
#include "networklayer.h"
#include "packetBuffer.h"
#include "timerdriver.h"


/*
** =============================================================================
**                   GLOBAL EXPORTED FUNCTION DECLARATIONS
** =============================================================================
*/


/**
 * Description:
 * @param:
 * @return:
*/

void mac_layer_init(PacketBuffer *pRxBuf, PacketBuffer *pTxBuf);
GLOB_RET mac_interface(char iKey);
GLOB_RET set_mac_address(uint8_t addr);
uint8_t get_mac_address(void);


/*
** ==========================================================================
**                        DEFINES and ENUMS 
** ==========================================================================
*/


/*
 ** ==========================================================================
 **                       Extern Global variables
 ** ==========================================================================
 */

extern mlme Mlme;


#endif //DCF_H