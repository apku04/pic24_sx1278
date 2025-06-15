/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system intialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  PIC24FJ64GB002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

//#include <stdio.h>
//#include <string.h>
#include <p24FJ64GB002.h>
#include "globalInclude.h"
#include "main.h"
#include "sx1278.h"
#include "../mcc_generated_files/system.h"
#include "timerdriver.h"
#include "terminal.h"

#include "usbdriver.h"
#include "networklayer.h"
#include "maclayer.h"
#include "packetBuffer.h"
#include "../mcc_generated_files/ext_int.h"



uint16_t seq = 0;

uint8_t dcfTask = 0;
slme SLME;

unsigned int pktTxCnt = 0;

uint8_t packet_transmit_count = 0;
uint8_t beacon_flag = 1;

PacketBuffer pRxBuf, pTxBuf;


void dcf_app_interface(Direction dcfTask, PacketBuffer *pRxBuf , PacketBuffer *pTxBuf);
void app_outgoing(Packet *pkt, PacketBuffer *pTxBuf);
void app_incomming( Packet *pkt, PacketBuffer *pTxBuf );
void beaconkHandler(void);


/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
   
    init_packet_buffer(&pRxBuf);
    init_packet_buffer(&pTxBuf);
    network_layer_init(&pRxBuf, &pTxBuf);
    mac_layer_init(&pRxBuf, &pTxBuf);
    user_layer_init(&pTxBuf);
    
    /* initialize function pointer to beaconkHandler */
    cb_timer ptr_comTaskHandler_cb = beaconkHandler;
    /* register the callback function */
    register_timer_cb(ptr_comTaskHandler_cb);
    
    RF_ON = 1;
    setup_lora(&pRxBuf, &pTxBuf);
    initiate_receiver();
    
    Direction dcfTask = OUTGOING;
    
    while (true)
    {
        dcf_app_interface(dcfTask, &pRxBuf, &pTxBuf);
        network_interface(dcfTask);
        mac_interface(dcfTask);

        switch(dcfTask) {
            case OUTGOING:
                dcfTask = INCOMING;
                break;
            case INCOMING:
                dcfTask = RETX;
                break;
            case RETX:
                dcfTask = OUTGOING;
                break;
            default:
                // Handle unexpected value
                break;
        }
    }

    return 1;
}

void beaconkHandler(void)
{
    if (GLOB_ERROR_BUFFER_FULL != buffer_full(&pTxBuf))
    {
        if(beacon_flag)
        {
            Packet pkt;
            seq++;
            pkt.pOwner = NET;
            pkt.pktDir = OUTGOING;

            pkt.control_app = BEACON;
            pkt.length = 4 + 0; // Add APP header + data
            pkt.sequence_num = seq;
            
            

            write_packet(&pTxBuf, &pkt);
        }
    }else {
        print("Buffer full\n\r");
    }
}


/*==============================================================================
** Function...: dcf_app_interface
** Return.....: GLOB_RET
** Description: main application layer
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void dcf_app_interface(Direction dcfTask, PacketBuffer *pRxBuf , PacketBuffer *pTxBuf)
{
    switch(dcfTask)
    { 
        case INCOMING:
        {
            Packet pkt = search_pending_packet(pRxBuf, INCOMING, APP);
            if(pkt.pktDir != DIR_EMPTY && pkt.pOwner != OWNER_EMPTY){
                app_incomming(&pkt, pTxBuf);
            }
            break;
        }
        case  OUTGOING:
        {
            Packet pkt = search_pending_packet(pTxBuf, OUTGOING, APP);
            if(pkt.pktDir != DIR_EMPTY && pkt.pOwner != OWNER_EMPTY){
                app_outgoing(&pkt, pTxBuf);
            }
            break;
        }

        default:
            break;
    }
}


/*==============================================================================
** Function...: app_outgoing
** Return.....: void
** Description: private function that handles all outgoing packets
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void app_outgoing(Packet *pkt, PacketBuffer *pTxBuf)
{
    if (GLOB_ERROR_BUFFER_FULL != buffer_full(pTxBuf))
    {
        seq++;
        pkt->pOwner = NET;
        pkt->pktDir = OUTGOING;
        
        pkt->control_app = PAYLOAD;
        pkt->length = pkt->length + 4; // Add APP header to total length
        pkt->sequence_num = seq;
        
        write_packet(pTxBuf, pkt);
    }else {
        print("Buffer full\n\r");
    }
}


/*==============================================================================
** Function...: app_incomming
** Return.....: void
** Description: private function that handles all incomming packets
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void app_incomming( Packet *pkt, PacketBuffer *pTxBuf )
{
        // EX_INT1_InterruptDisable();
        // EX_INT1_InterruptEnable();
    packet_print_out(1, NULL, pkt);
    
    if(pkt->control_app == PING)
    {
        Packet pkt;

        // Initialize the packet data with null characters.
        // The size of pkt.data should be defined somewhere as 50 or more.
        memset(pkt.data, 0, sizeof(pkt.data));

        pkt.pOwner = NET;
        pkt.pktDir = OUTGOING;
        pkt.control_app = PONG;

        pkt.length = 4 + 0; // Add APP header + data

        // Send the packet if the buffer is not full.
        if (buffer_full(pTxBuf) != GLOB_ERROR_BUFFER_FULL) {
            write_packet(pTxBuf, &pkt);
        } else {
            print("Buffer full\n");
        }
    }
    //print_routing_table();
}

void send_beacon_flag(uint8_t flag)
{
    beacon_flag = flag;
}

