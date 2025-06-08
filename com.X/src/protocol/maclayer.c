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
        File name: dcf.c
        Version:   v0.0
        Date:      2015-12-28
    ============================================================================
 */


/*
** =============================================================================
**                        INCLUDE STATEMENTS
** =============================================================================
*/

#include "maclayer.h"
#include "../mcc_generated_files/tmr1.h"


/*
** =============================================================================
**                   LOCAL FUNCTION DECLARATIONS
** =============================================================================
*/

GLOB_RET backOff(void);
void selectBackoff(void);
void selectCW(void);
GLOB_RET basicDCF(void *frame);
GLOB_RET mac_outgoing(unsigned char addr, unsigned char len, void *frame );
GLOB_RET mac_incoming( void *frame, char len);

/*
** ==========================================================================
**                       Layer specific variables
** ==========================================================================
*/

mlme Mlme;
char carrierDetect;


/*
** =============================================================================
**                  EXPORTED  FUNCTIONS
** =============================================================================
*/


GLOB_RET set_mac_address(uint8_t addr) {
    if (addr < 1 || addr > 254) {
        return GLOB_ERROR_OUT_OF_RANGE_PARAM;
    }
    Mlme.mAddr = addr;
    return GLOB_SUCCESS;
}

uint8_t get_mac_address(void) {
    return Mlme.mAddr;
}

GLOB_RET set_use_csma(uint8_t use_csma) {
    Mlme.mUseCSMA = use_csma;
    return GLOB_SUCCESS;
}

uint8_t get_use_csma(void) {
    return Mlme.mUseCSMA;
}


/*
** =============================================================================
**                    FUNCTIONS
** =============================================================================
*/

/*==============================================================================
** Function...: dcfInit
** Return.....: GLOB_RET
** Description: dataLink
** Created....: 24.08.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void dcfInit(void)
{
    Mlme.headerSize = 4;
    Mlme.mAddr = 0;
    Mlme.mACKTimeOut = 200;
    Mlme.macFrameSize = 0;
    Mlme.mUseCSMA = 0;
    
    Mlme.mBackoffTimer = 0;
    Mlme.mCWmax = 128;
    Mlme.mCWmin = 8;
    Mlme.mCurrentCW = Mlme.mCWmin;
    Mlme.mExpectACK = NO;
    Mlme.mExpectPAY = YES;
    Mlme.mGotACK = NO;
    Mlme.mGotPAY = NO;
    Mlme.mMACdrop = 6;
    Mlme.mPAYTimeOut = 84;
    Mlme.mSIFSTime = 8;
    Mlme.mSlotTime = 8;
    Mlme.mDIFSTtime = 24;
    Mlme.mBcast = YES;

    // Seed the PRNG using the running timer to ensure varying values
    srand(TMR1_Counter16BitGet());
}

/*==============================================================================
** Function...: channel_access
** Return.....: GLOB_RET
** Description: dataLink
** Created....: 24.08.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/

GLOB_RET channel_access(void *frame, unsigned char retCode)
{
    GLOB_RET ret = GLOB_FAILURE;
    
    switch (retCode)
    {
        //Wait DIFS period, if there is carrierDetect then freeze the counter
        case WAIT_DIFS:
            START_DIFS_TIMER;
            ret = DATA_LINK_DIFS_WAIT_OK;
            while( difsTimer < Mlme.mDIFSTtime)
            {
                if(carrierDetect)
                { 
                    LED_RED_1 = 1;
                    while(carrierDetect)
                    {
                        //FIXME: can do something use full, instead of wile? 
                    }
                    LED_RED_1 = 0;
                }
            }
            break;
            
        case PERFORM_BACKOFF:
            if(DATA_LINK_CARRIER_DETECTED==backOff())
            {
                //if carrierDetect then return:
                return DATA_LINK_CARRIER_DETECTED;
            }
            else
            {
                //else no carrierDetect then do the transmit 
                ret = DATA_LINK_BACKOFF_OK;
            }
            break;
            
        case SEND_PAY:
            ret = transmitFrame(frame, Mlme.macFrameSize);
            break;
            
        case WAIT_FOR_ACK:
            START_ACK_TIMER;
            //Block until ACK is received or timeout
            while( ackTimer < Mlme.mACKTimeOut && Mlme.mGotACK == NO );
             // ACK received ?
            if(Mlme.mGotACK)
            {
                ret = DATA_LINK_GOT_ACK;
                LED_GREEN_1_TOGGLE;
            }
            else
            {
                ret = DATA_LINK_ACK_TIMEOUT;
            }
            
            break;
            
        default:
            ret = GLOB_ERROR_INVALID_PARAM;
            break; 
    }
    
    return ret;
}


/*==============================================================================
** Function...: basicDCF
** Return.....: GLOB_RET
** Description: dataLink
** Created....: 24.08.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/

GLOB_RET basicDCF(void *frame)
{
    GLOB_RET ret = GLOB_FAILURE;
    
    // Wait DIFS
    ret = channel_access(frame, WAIT_DIFS);
    if(DATA_LINK_DIFS_WAIT_OK == ret)
    {
        // Select a new backoff window if the backofftimer is == 0
        if(Mlme.mBackoffTimer == 0) selectBackoff();
        ret = channel_access(frame, PERFORM_BACKOFF);
        if(DATA_LINK_BACKOFF_OK==ret)
        {
            // send the payload
            channel_access(frame, SEND_PAY);
            // now we have transmitted a PAYload and we don't expect a payload
            Mlme.mExpectPAY = NO;
            // we  expect an ack
            Mlme.mExpectACK = YES;
            // reconf. the nrf driver to receive an ACK packet (size of header) 
            recieveMode();
            // wait for ACK if not broadcast
            if(Mlme.mBcast || !Mlme.mUseCSMA)
            {
                LED_GREEN_1_TOGGLE;
                ret = DATA_LINK_GOT_ACK;
            }
            else 
            {
                ret = channel_access(frame, WAIT_FOR_ACK);
            }
            // we got ack
            if(DATA_LINK_GOT_ACK == ret)
            {
                //set the CW size to the default min
                Mlme.mCurrentCW = Mlme.mCWmin;
                ret = GLOB_SUCCESS;
            }
            //no ack/ack timed out
            else
            {
                selectCW();
                ret = DATA_LINK_ACK_TIMEOUT;
            }
        }
        else
        {
            ret = DATA_LINK_CARRIER_DETECTED;
        }
    }
    
    Mlme.mExpectPAY = YES;
    Mlme.mExpectACK = NO;
    Mlme.mGotACK = NO;
    
    recieveMode();
    return ret;
}


/*==============================================================================
** Function...: mac_interface
** Return.....: GLOB_RET
** Description: medium layer interface. All call must go through this interface
** Created....: 04.04.2013 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET mac_interface(char iKey, char addr, char len, void *frame)
{
    GLOB_RET ret = GLOB_SUCCESS;

    if(OUTGOING==iKey)
    {
        ret = mac_outgoing(addr, len, frame);
    }
    else if (INCOMING == iKey)
    {
        ret = mac_incoming(frame, len);
    }
    else
    {
        ret = GLOB_ERROR_INVALID_PARAM;
    }
    return ret;
}


/*==============================================================================
** Function...: mac_incoming
** Return.....: GLOB_RET
** Description: private function that handles all incomming packets
** Created....: 01.05.2015 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
GLOB_RET mac_incoming( void *frame, char len)
{
    uint8_t macFrame[64];
    memcpy(macFrame, frame, len);  
    
    uint8_t rx_dest_addr = macFrame[3];
    
    if ( (255 == rx_dest_addr) || (Mlme.mAddr == rx_dest_addr)) {
        network_interface(INCOMING, 0, len-6, &macFrame[7]);
    }
    
    
    GLOB_RET ret = GLOB_SUCCESS;
    
    return ret;
}


/*==============================================================================
** Function...: sendPacket
** Return.....: GLOB_RET
** Description: session** Description: session

** Created....: 09.08.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/

GLOB_RET mac_outgoing(uint8_t addr, uint8_t len, void *frame)
{
    GLOB_RET ret;
    int i = 0; // MAC retrans. counter
    uint8_t macFrame[64]; // Set a suitable size based on your application requirements
    Mlme.macFrameSize = len + Mlme.headerSize;
    char seq = 0, con = 0;
    char s[30];

    if (Mlme.macFrameSize > sizeof(macFrame)) {
        return GLOB_ERROR_MEMORY_ALLOCATION;
    }

    memcpy(macFrame, &addr, 1);           // Dest
    memcpy(macFrame + 1, &Mlme.mAddr, 1); // Src
    memcpy(macFrame + 2, &seq, 1);        // Sec
    memcpy(macFrame + 3, &con, 1);        // Control
    memcpy(macFrame + 4, frame, len);     // Data

    //op_hexdump(1, "----- MAC LAYER ----", macFrame, Mlme.macFrameSize, true);

    if (255 == addr) {
        Mlme.mBcast = YES;
    } else {
        Mlme.mBcast = NO;
    }

    while (i < Mlme.mMACdrop) // re-Send the packet i'th times before dropping it
    {
        ret = basicDCF(macFrame); // Simple CSMA/CA MAC
        // If Carrier detect wait untill !carrierDetect
        if (DATA_LINK_CARRIER_DETECTED == ret)
            while (carrierDetect)
                ;
        // if ret = no ack then we do retransmission
        else if (DATA_LINK_ACK_TIMEOUT == ret) {
            i++; // MAC retrans. counter
        }
        // if ret = success, we reset the contention window cw to initial val.
        else if (GLOB_SUCCESS == ret) {
            // Setting contention window to initial val.
            Mlme.mCurrentCW = Mlme.mCWmin;
            return GLOB_SUCCESS; // return to the caller with success
        }
        // The tranmission is not a success we reset the contention window
    }
    Mlme.mCurrentCW = Mlme.mCWmin;
    LED_RED_1_TOGGLE;

    sprintf(s, "ACK TIMEOUT ret = %d\n", ret);
    print(s);

    return DATA_LINK_TRANSMISSION_FAILED;
}


/*==============================================================================
** Function...: backOff
** Return.....: GLOB_RET
** Description: dataLink
** Created....: 24.08.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/

GLOB_RET backOff(void)
{
    START_SLOT_TIMER;
    // countdown to 0 while no carrierDetect if carrierDetect return 1 
    while(!carrierDetect)
    {
        if(slotTimer >= Mlme.mSlotTime)
        {
            Mlme.mBackoffTimer--; 
            START_SLOT_TIMER;
        }
        if(Mlme.mBackoffTimer == 0)  // FIXME Magic number
        {
            return DATA_LINK_BACKOFF_OK;
        }
    }
    return DATA_LINK_CARRIER_DETECTED;    
}


/*==============================================================================
** Function...: selectBackoff
** Return.....: void
** Description: dataLink
** Created....: 24.08.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/

void selectBackoff(void)
{
  //char s[90];

  // get a random number within [0-cw]
  Mlme.mBackoffTimer = ( rand() % Mlme.mCurrentCW ) + 1;
  //sprintf(s,"selectBackoff | Mlme.mBackoffTimer %d\n", Mlme.mBackoffTimer);
  //print(s);
}


/*==============================================================================
** Function...: selectCW
** Return.....: void
** Description: dataLink
** Created....: 24.08.2012 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/

void selectCW(void)
{
  //char s[90];
  if( Mlme.mCurrentCW< Mlme.mCWmax )
  {
    Mlme.mCurrentCW = 2*Mlme.mCurrentCW; 
    //sprintf(s,"selectCW | Mlme.mCurrentCW %d\n", Mlme.mCurrentCW);
    //print(s);
  }
}