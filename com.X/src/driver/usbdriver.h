
#ifndef USBDRIVER_H
#define	USBDRIVER_H

#include <xc.h> 
#include "../../mcc_generated_files/usb/usb.h"

int usbdriver_init(void);
void usbdriver_handler(void);
bool usb_print( void* data );

#endif	/* USBDRIVER_H */

