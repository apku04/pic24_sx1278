#ifndef FLASH_HANDLER_H
#define	FLASH_HANDLER_H

#include "flash.h"
#include "globalInclude.h"

void writeFlash(deviceData_t* data);
void readFlash(addrEnum addr, uint8_t* read_data);

#endif	/* FLASH_H */

