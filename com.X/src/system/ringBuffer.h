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
        File name: ringBuffer.h
        Version:   v0.0
        Date:      2012-08-09
    ============================================================================
 */

/*
** ==========================================================================
**                        INCLUDE STATEMENTS
** ==========================================================================
*/

#ifndef RINGBUFF_H
#define	RINGBUFF_H

#include "main.h"
#include "globalInclude.h"

/*
** ==========================================================================
**                        DEFINES AND MACROS
** ==========================================================================
*/

/*
** =============================================================================
**                       EXPORTED FUNCTION DECLARATION
** =============================================================================
*/

/* 
 * Checks if the buffer is full.
 * @param bPar: Pointer to a buffer parameter structure.
 * @return: GLOB_ERROR_BUFFER_FULL if the buffer is full, GLOB_SUCCESS otherwise.
 */
GLOB_RET buffer_full(rBufPar *bPar);

/*
 * Checks if the buffer is empty.
 * @param bPar: Pointer to a buffer parameter structure.
 * @return: GLOB_ERROR_BUFFER_EMPTY if the buffer is empty, GLOB_SUCCESS otherwise.
 */
GLOB_RET buffer_empty(rBufPar *bPar);

/*
 * Writes data to the buffer.
 * @param dPtr: Pointer to the data to be written to the buffer.
 * @param bPar: Pointer to a buffer parameter structure.
 * @return: GLOB_SUCCESS on successful write, appropriate error code otherwise.
 */
GLOB_RET write_buffer(uint8_t *dPtr, rBufPar *bPar);

/*
 * Reads data from the buffer.
 * @param dPtr: Pointer to a location where the read data will be stored.
 * @param bPar: Pointer to a buffer parameter structure.
 * @return: GLOB_SUCCESS on successful read, appropriate error code otherwise.
 */
GLOB_RET read_buffer(uint8_t *dPtr, rBufPar *bPar);

#endif	/* RINGBUFF_H */