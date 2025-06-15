#include "timerdriver.h"

// Delay timer used with Timer 1

static uint32_t delayMs_t = 0;
uint32_t difsTimer = 0;
uint32_t ackTimer = 0;
uint32_t slotTimer = 0;

uint32_t beaconTimer = 0;

static cb_timer ptr_reg_tx_cb;
static uint8_t tx_cb_flag = 0;



static cb_timer ptr_reg_tx_cb;


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
    beaconTimer++;
    
    if( delayMs_t==UINT32_MAX)
    {
        delayMs_t = 0;
    }
    
    if(tx_cb_flag && ( beaconTimer == (600000) ) ) //3600000 = 60minW
    {
        (*ptr_reg_tx_cb)();
        beaconTimer = 0;
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

/*------------------------------------------------------------------------------
** Function...: register_timer_tx_cb
** Return.....: void
** Description: registration of timer callback functions
** Created....: 26.07.2023 by Achuthan
** Modified...: dd.mm.yyyy by nn
------------------------------------------------------------------------------*/
void register_timer_cb(cb_timer ptr_reg_cb)
{
    ptr_reg_tx_cb = ptr_reg_cb;
    tx_cb_flag = 1;                           
}

