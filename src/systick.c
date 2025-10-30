#include "../inc/systick.h"

#define CTRL_ENABLE (1U<<0)
#define CTRL_CLKSRC (1U<<2)
#define CTRL_COUNTFLAG (1U<<16)

void systick_msec_delay(uint32_t delay){
    //#Of clock cycles in 1 msec
    Systick->LOAD=ONE_MSEC_LOAD_1;
    Systick->VAL=0;
    //Select internal clock source
    Systick->CTRL=CTRL_CLKSRC;
    //Enable
    Systick->CTRK|=CTRL_ENABLE;
    for (int i=0; i<delay; i++){
        while(!(Systick->CTRL & CTRL_COUNTFLAG)){}
    }
    Systick->CTRL=0;
}