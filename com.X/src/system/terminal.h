/*  ============================================================================
    Copyright (C) 2015 Achuthan Paramanathan.
    All rights reserved.
    ============================================================================
    This document contains proprietary information belonging to 
    Achuthan Paramanathan. Passing on and copying of this document, use and 
    communication of its contents is not permitted without prior written 
    authorisation.
    ============================================================================
    Revision Information:
        File name: terminal.h
        Version:   v0.0
        Date:      2012-08-09
    ============================================================================
 */

/*
** ==========================================================================
**                        INCLUDE STATEMENTS
** ==========================================================================
*/

#ifndef TERMINAL_H
#define	TERMINAL_H

#include "usbdriver.h"

typedef struct {
    PacketBuffer *pktRxBuf;
    PacketBuffer *pktTxBuf;
} ulme;

/*
** =============================================================================
**                       EXPORTED FUNCTION DECLARATION
** =============================================================================
*/

void terminal( uint8_t *msg, uint8_t size );
void user_layer_init(PacketBuffer *pTxBuf);
void simpleRegPrint(void);
void detailRegPrint(void);
const char *byte_to_binary(int x);
void printHeader(void* msg);
void print_logo(void);
void menu(uint16_t argc, uint8_t *argv[]);


#endif	/* TERMINAL_H */