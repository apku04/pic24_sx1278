/*
 * File:   usbdriver.c
 * Author: Achuthan
 *
 * Created on September 22, 2018, 5:59 PM
 */

#include <string.h>
#include "../globalInclude.h"
#include "usbdriver.h"
#include "terminal.h"
#include "../src/driver/timerdriver.h"

int usbdriver_init(void) 
{
    return 0;
}


void usbdriver_handler(void)
{
    uint8_t readBuffer[255];
    
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    if( USBIsDeviceSuspended()== true )
    {
        return;
    }

    if( USBUSARTIsTxTrfReady() == true)
    {

        uint8_t numBytesRead;

        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
        
        //sprintf(s, "echo %s\0\r\n",readBuffer );
        

        if(numBytesRead > 0)
        {
            terminal( readBuffer, numBytesRead );
            //putUSBUSART(s,5+numBytesRead);
        }
    }

    CDCTxService();
}



bool usb_print(void *data) {
    bool ret = false;
    int retries = 3;

    while (retries > 0) {
        if (USBUSARTIsTxTrfReady()) {
            putsUSBUSART((char *)data);
            ret = true;
            break;
        } else {
            LED_RED_1_TOGGLE;
            retries--;
            delay_ms(200);
        }
    }
    return ret;
}
