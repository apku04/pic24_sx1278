#include "timerdriver.h"

// Delay timer used with Timer 1

static uint32_t delayMs_t = 0;
uint32_t difsTimer = 0;
uint32_t ackTimer = 0;
uint32_t slotTimer = 0;


/*------------------------------------------------------------------------------
** Function...: timer_driver
** Return.....: void
** Description: millisecond delay
** Created....: 25.02.2017 by Achuthan
** Modified.static uint32_t..: dd.mm.yyyy by nn
------------------------------------------------------------------------------*/
void timer_driver(void) {
    
    delayMs_t++;
    difsTimer++;
    slotTimer++;
    ackTimer++;
    
    if( delayMs_t==UINT32_MAX)
    {
        delayMs_t = 0;
    }
}


/*------------------------------------------------------------------------------
** Function...: delay_ms
** Return.....: void
** Description: millisecond delay
** Created....: 25.02.2017 by Achuthan
** Modified...: dd.mm.yyyy by nn
------------------------------------------------------------------------------*/
void delay_ms(uint32_t t) {
  delayMs_t = 0;
  while (delayMs_t < t)
    ;
}

