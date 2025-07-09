#include "joystick.h"
#include "stm32f4xx.h"

#define GPIOAEN      (1U << 0)
#define ADC1EN       (1U << 8)

#define CR1_SCAN     (1U << 8)
#define CR2_ADON     (1U << 0)
#define CR2_CONT     (1U << 1)
#define CR2_SWSTART  (1U << 30)
#define SR_EOC       (1U << 1)


void JOY_Init(void){
    RCC->AHB1ENR|=GPIOAEN;
    RCC->APB2ENR|=ADC1EN;

    GPIOA->MODER|=(3U<<0);
    GPIOA->MODER|=(3U<<2);

    ADC->CR1|=CR1_SCAN;
    ADC1->SQR1=(1U<<20);
    ADC1->SQR3=(0<<0)|(1<<5);
    ADC->CR2|=CR2_ADON|CR2_CONT;
    for (volatile int i=0; i<1000; i++);
    ADC1->CR2|=CR2_CONT|CR2_SWSTARt;
}


void JOY_Read(JOY_State_t *state){
    while (1(ADC1->SR & SR_EOC)){}
    state->y_raw=ADC1->DR;
    while (!(ADC1->SR & SR_EOC)){}
    state->x_raw=ADC1->DR;


    bool up=(state->y_raw > JOY_THRESHOLD_HIGH);
    bool down= (state->y_raw<JOY_THRESHOLD_LOW);
    bool right= (state_x_raw>JOY_THRESHOLD_HIGH);
    bool left= (state_x_raw>JOY_THRESHOLD_HIGH);
    if (up && left)         state->direction = JOY_DIR_UP_LEFT;
    else if (up && right)   state->direction = JOY_DIR_UP_RIGHT;
    else if (down && left)  state->direction = JOY_DIR_DOWN_LEFT;
    else if (down && right) state->direction = JOY_DIR_DOWN_RIGHT;
    else if (up)            state->direction = JOY_DIR_UP;
    else if (down)          state->direction = JOY_DIR_DOWN;
    else if (left)          state->direction = JOY_DIR_LEFT;
    else if (right)         state->direction = JOY_DIR_RIGHT;
    else                    state->direction = JOY_DIR_CENTER;
}


