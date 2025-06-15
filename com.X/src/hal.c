#include <stddef.h>
#include "hal.h"

uint16_t swap_bytes(uint16_t val);


uint16_t swap_bytes(uint16_t val) {
    return (val << 8) | (val >> 8);
}


void recieveMode( void )
{
    initiate_receiver();
}

GLOB_RET transmitFrame (Packet *pkt)
{
    GLOB_RET errorCode = GLOB_FAILURE;
    uint8_t payload[70];
    
    size_t size_to_copy = sizeof(Packet) - offsetof(Packet, destination_adr);
    
    memcpy(payload, (uint8_t *)pkt + offsetof(Packet, destination_adr), size_to_copy);

    errorCode = send(payload, size_to_copy);
    
    if (0 == errorCode)
    {
        if(pkt->control_app == PAYLOAD && pkt->pktDir != RETX)
        {
            print("Done\n");
            delay_ms(100);
            
        }
        errorCode = GLOB_SUCCESS;
    }
    
    return errorCode;
}



bool print(void* data) 
{
    return usb_print(data);
}