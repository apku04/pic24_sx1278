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

#include "sx1278.h"
#include "../mcc_generated_files/system.h"
#include "timerdriver.h"
#include "main.h"
#include "usbdriver.h"
#include "globalInclude.h"
#include "ringBuffer.h"
#include "networklayer.h"
#include "maclayer.h"
#include "../mcc_generated_files/ext_int.h"


uint8_t dcfTask = 0;
slme SLME;

unsigned int pktTxCnt = 0;

uint8_t packet_transmit_count = 0;


void dcf_app_interface(Direction dcfTask);
void app_outgoing(void);
void app_incomming(void);


/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    RF_ON = 1;
    setupLora();
    
    initiate_receiver();
    
    opmInit();
    dcfInit();
    
    Direction dcfTask = OUTGOING;
    while (true)
    {
        dcf_app_interface(dcfTask);
        dcfTask = (dcfTask == OUTGOING) ? INCOMING : OUTGOING;
    }

    return 1;
}


/*==============================================================================
** Function...: dcf_app_interface
** Return.....: GLOB_RET
** Description: main application layer
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void dcf_app_interface(Direction dcfTask)
{
    switch(dcfTask)
    {
        case INCOMING:
            app_incomming();
            break;

        case  OUTGOING:
            app_outgoing();
            break;

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
void app_outgoing(void)
{
    if (GLOB_ERROR_BUFFER_EMPTY != buffer_empty(&txBuf))
    {
        const size_t max_data_size = 50;
        const int destination = 255;
        uint8_t data[PACKET_SIZE];
        uint8_t len = 0;
        
        data[0] = 1;
        
        
        uint8_t fixed_buffer[PACKET_SIZE];
        EX_INT1_InterruptDisable();
        read_buffer(fixed_buffer, &txBuf); // Read into fixed_buffer
        EX_INT1_InterruptEnable();

        // Copy up to max_data_size bytes from fixed_buffer to data, stopping at the null terminator
        size_t i;
        for (i = 0; i < max_data_size && fixed_buffer[i] != '\0'; i++) {
            data[1 + i] = fixed_buffer[i];
        }
        data[1 + i] = '\0'; // Add null terminator to the end of the data
        len = 1 + i;
        
        if ( i+1 > max_data_size)
        {
            len = max_data_size;
            print("Packet size is too long, sat to max");
            delay_ms(100);
            
        }

        
        data[1] = 1+i;
        initiate_sender();

        //op_hexdump(1, "----- APP LAYER ----", data, len, true);

        // Send data over network interface
        if (network_interface(OUTGOING, destination, (1+i), data) == -1)
        {
            print("Error: Failed to send data over network interface\n");
        }
        else
        {
            print("Transmission completed\n");
        }

        // Update packet transmit count
        packet_transmit_count++;
    }
}



/*==============================================================================
** Function...: app_incomming
** Return.....: void
** Description: private function that handles all incomming packets
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void app_incomming(void)
{
    if (GLOB_ERROR_BUFFER_EMPTY != buffer_empty(&rxBuf))
    {
        EX_INT1_InterruptDisable();
        uint8_t fixed_buffer[64];
        uint8_t data[64];
        read_buffer(fixed_buffer, &rxBuf);
        EX_INT1_InterruptEnable();
        
        
        uint8_t len = fixed_buffer[1];
        
        memcpy(data, &fixed_buffer[2], len );
        
        data[len] = '\0';
        
        op_hexdump(1, "----- <RX> ----", data, len, false);

    }
}

