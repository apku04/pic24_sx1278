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
        File name: ringBuffer.c
        Version:   v0.0
        Date:      23-07-2015
    ============================================================================
 */

/*
 ** ============================================================================
 **                        INCLUDE STATEMENTS
 ** ============================================================================
 */

#include <stdio.h>
#include "usbdriver.h"
#include "ringBuffer.h"




/*
** =============================================================================
**                                   GLOBAL VARIABLES
** =============================================================================
*/

rBufPar txBuf, rxBuf;

/*
 ** ============================================================================
 **                   LOCAL EXPORTED FUNCTION DECLARATIONS
 ** ============================================================================
 */

/*==============================================================================
 ** Function...: ringBuffer_init
 ** Return.....: void
 ** Description: Ring buffer initialization
 ** Created....: 23.07.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void ringBuffer_init(void) {}

/*==============================================================================
 ** Function...: buffer_full
 ** Return.....: GLOB_RET, return GLOB_ERROR_BUFFER_FULL if full
 ** Description: is buffer full?
 ** Created....: 23.07.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET buffer_full(rBufPar *bPar) {
  char s[96];

  GLOB_RET errorCode = GLOB_SUCCESS;
  
  // Buffer size exceeds the defined total size
  if (bPar->data_size > BUFFER_SIZE) {
    sprintf(s, "LOG_ERROR 2\n");
    usb_print(s);
    errorCode = GLOB_ERROR_BUFFER_SIZE_EXCEEDED;
  }
  // Buffer size is below 0
  else if (bPar->data_size < 0) {
    sprintf(s, "LOG_ERROR 3\n");
    usb_print(s);
    errorCode = GLOB_ERROR_BUFFER_SIZE_NEGATIVE;
  }
  // Read and write pointer exceeds the defined total size
  if (bPar->read_pointer != bPar->write_pointer &&
      bPar->data_size == BUFFER_SIZE) {
    sprintf(s, "LOG_ERROR 4\n");
    usb_print(s);
    errorCode = GLOB_ERROR_POINTER_MISMATCH;
  }
  
  if(bPar->read_pointer == bPar->write_pointer &&
         bPar->data_size == BUFFER_SIZE)
  {
      errorCode = GLOB_ERROR_BUFFER_FULL;
  }

  return errorCode;
}

/*==============================================================================
 ** Function...: buffer_empty
 ** Return.....: GLOB_RET 
 ** Description: is buffer empty?
 ** Created....: 23.07.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET  buffer_empty(rBufPar *bPar) {
  char s[96];
  
  GLOB_RET errorCode = GLOB_SUCCESS;

  // Buffer size exceeds the defined total size
  if (bPar->data_size > BUFFER_SIZE) {
    sprintf(s, "LOG_ERROR 6\n");
    usb_print(s);
    errorCode = GLOB_ERROR_BUFFER_SIZE_EXCEEDED;
  }
  // Buffer size is below 0
  else if (bPar->data_size < 0) {
    sprintf(s, "LOG_ERROR 7\n");
    usb_print(s);
    errorCode = GLOB_ERROR_BUFFER_SIZE_NEGATIVE;
  }
  if (bPar->read_pointer != bPar->write_pointer && bPar->data_size == 0) {
    sprintf(s, "LOG_ERROR 8\n");
    usb_print(s);
    errorCode = GLOB_ERROR_POINTER_MISMATCH;
  }
  
  if (bPar->read_pointer == bPar->write_pointer && bPar->data_size == 0)
  {
      errorCode = GLOB_ERROR_BUFFER_EMPTY;
  }

  return errorCode;
}

/*==============================================================================
 ** Function...: write_buffer
 ** Return.....: GLOB_RET
 ** Description: Write to the ring buffer
 ** Created....: 23.07.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET write_buffer(uint8_t *dPtr, rBufPar *bPar) {
  char s[96];
  GLOB_RET errorCode = GLOB_SUCCESS;
  
  if (buffer_full(bPar)) {
        return GLOB_ERROR_BUFFER_FULL;
    }
  // Buffer size exceeds the defined total size
  if (bPar->data_size > BUFFER_SIZE) {
    sprintf(s, "LOG_ERROR 10\n");
    usb_print(s);
    errorCode = GLOB_ERROR_WRITE_BUFFER_SIZE_EXCEEDED;
  }

  if (++bPar->write_pointer >= BUFFER_SIZE)
    bPar->write_pointer = 0;
  memcpy(bPar->buffer[bPar->write_pointer], dPtr, BUFFER_DATA_SIZE);

  if (bPar->data_size >= BUFFER_SIZE) {
    sprintf(s, "LOG_ERROR 11\n");
    usb_print(s);
    errorCode = GLOB_ERROR_WRITE_BUFFER_DATA_SIZE_EXCEEDED;
  } else {
    bPar->data_size++;
  }
  return errorCode;
}

/*==============================================================================
 ** Function...: read_buffer
 ** Return.....: GLOB_RET
 ** Description: Read from ring buffer
 ** Created....: 23.07.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET read_buffer(uint8_t *dPtr, rBufPar *bPar) {
  char s[96];
  
  GLOB_RET errorCode = GLOB_SUCCESS;
  
  if (buffer_empty(bPar)) {
        return GLOB_ERROR_BUFFER_EMPTY;
    }
  if (bPar->data_size > BUFFER_SIZE) {
    sprintf(s, "LOG_ERROR 12\n");
    usb_print(s);
     errorCode = GLOB_ERROR_READ_BUFFER_SIZE_EXCEEDED;
  }
  if (!buffer_empty(bPar)) {
    if (++bPar->read_pointer >= BUFFER_SIZE)
      bPar->read_pointer = 0;
    if (bPar->data_size <= 0) {

    } else {
      bPar->data_size--;
    }
    memcpy(dPtr, bPar->buffer[bPar->read_pointer], BUFFER_DATA_SIZE);
    memset(bPar->buffer[bPar->read_pointer], '0', BUFFER_DATA_SIZE);
  } else {
    usb_print("INVALID READ BUF!\n");
  }
   return errorCode;
}