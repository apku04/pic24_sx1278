/*  ============================================================================
    Copyright (C) 2015 Achuthan Paramanathan.
    All rights reserved.
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
        File name: timerdriver.h
        Version:   v0.0
        Date:      2012-08-09
    ============================================================================
 */

#ifndef TIMERDRIVER_H
#define TIMERDRIVER_H

#include <stdint.h> /* For uint32_t definition */

typedef void (*cb_timer)(void);
void register_timer_cb(cb_timer ptr_reg_cb);


void timer_driver(void);

void delay_ms(uint32_t t);


#endif /* TIMERDRIVER_H */