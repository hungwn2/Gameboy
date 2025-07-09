#include "game_engine.h"
#include <stdlib.h>




typedef enum{
    STATE_INIT,
    STATE_TITLE_SCREEN,
    STATE_START_LEVEL,
    STATE_PLAYING,
    STATE_PLAYER_DIED,
    STATE_PAUSED,
    STATE_GAME_OVER,
    STATE_LEVEL_COMPLETE
} GameState_t;

GameState_t g_current_game_state=STATE_INIT();


int main(void){
    HAL_Init();
    SystemClock_Config();
    GPIO_Init();
    SPI_INit();
    TIM6_INIt();
    ADC1_Init();
    DMA_Init();

    while(1){
        int main (void)
{
    Mario_init();
    Mario_display_start_screen();
        while(1){
            if(frameUpdate == SET){
                RTE_display_score();
                RTE_update_player_spaceship(&PlayerSpaceship);
                RTE_draw_player_spaceship(&PlayerSpaceship);
                RTE_create_rocket(&RocketVect,Rocket,&PlayerSpaceship);
                RTE_update_rocket(&RocketVect,&AsteroidVect);
                RTE_draw_rocket(&RocketVect);
                RTE_update_asteroid(&AsteroidVect,&PlayerSpaceship);
                RTE_draw_asteroid(&AsteroidVect);
            
            if(PlayerSpaceship.Object_Property.aliveFlag == RTE_ALIVE_FALSE){
                PROTOBOARD_GREEN_LED_ON;
                RTE_display_game_over_screen();
                while(SHOOT_BUTTON_READ);
                RTE_reset_game();
                PROTOBOARD_GREEN_LED_OFF;
                break;
            }
            
            if(AsteroidVect.total == 0){
                TIM_ctr(TIM6,STOP);
                currentWave++;
                RNG_init();
                RTE_create_asteroid(&AsteroidVect,Asteroid,numOfAsteroidInWave[currentWave],&PlayerSpaceship);
                TIM_ctr(TIM6,START);
            }
            frameUpdate = CLEAR;
        }
    }
    }
}
    }
}