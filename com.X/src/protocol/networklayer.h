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
        File name: opm.h
        Version:   v0.0
        Date:      2012-08-09
    ============================================================================
 */

/*
** ==========================================================================
**                        INCLUDE STATEMENTS
** ==========================================================================
*/

#ifndef OPM_H
#define	OPM_H

#include <stdlib.h> 
#include <math.h>

#include "globalInclude.h"
#include "networklayer_defs.h"


/*
** =============================================================================
**                   GLOBAL EXPORTED FUNCTION DECLARATIONS
** =============================================================================
*/

GLOB_RET network_interface(Direction iKey);
void network_layer_init(PacketBuffer *pRxBuf, PacketBuffer *pTxBuf);
RoutingEntry* get_routing_table(void);
uint8_t get_routing_entries(void);

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

#endif //OPM_H