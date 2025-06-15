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
        File name: sx1278.h
        Version:   v0.0
        Date:      2019-10-11
    ============================================================================
 */

#ifndef SX1278_H
#define SX1278_H

#include <stdint.h>
#include "globalInclude.h"

void print_all_registers(void);
uint8_t setup_lora(PacketBuffer *pRxBuf, PacketBuffer *pTxBuf);
uint8_t send(uint8_t *payload, uint8_t length);
uint8_t initiate_receiver(void);
uint8_t initiate_sender(void);
uint16_t SPI1_Exchange8bitBuffer(uint8_t *dataTransmitted, uint16_t byteCount, uint8_t *dataReceived);
void radio_irq_handler( void );
uint8_t sx1278_get_carrier_detect_average(void);


uint8_t sx1278_set_channel(uint32_t freq);
uint32_t sx1278_get_channel(void);
void sx1278_set_datarate(uint8_t data_rate);
uint8_t sx1278_get_datarate(void);
void sx1278_set_tx_power(uint8_t power);
uint8_t sx1278_get_tx_power(void);


#endif /* SX1278_H */