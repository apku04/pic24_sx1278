#include "globalInclude.h"
#include "sx1278.h" 
#include "usbdriver.h"
#include "timerdriver.h"


void recieveMode( void );
GLOB_RET transmitFrame (Packet *pkt);
bool print(void* data);