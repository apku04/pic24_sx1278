
#include "hal.h"






void recieveMode( void )
{
    initiate_receiver();
}

GLOB_RET transmitFrame(void* data, uint8_t len)
{
    GLOB_RET errorCode = GLOB_FAILURE;
    
    errorCode = send((uint8_t*) data, len);
    
    if (0 == errorCode)
    {
        errorCode = GLOB_SUCCESS;
    }
    
    return errorCode;
}

bool print(void* data) 
{
    return usb_print(data);
}