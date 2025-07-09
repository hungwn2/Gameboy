#include "main.h"
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FRAME_RATE 30


//physics constants
#define GRAVITY 0.5f
#define PLAYER_SPEED 2.5f
#define JUM_FORCE 10.0f
#define MAX_FALL_SPEED 8.0f


typedef struct{
    float x;
    float y;
    float dx, dy;
    float width, height
    float vx;
    float vy;
    bool is_alive;
    bool on_ground;
}GameObject Properties_t;

typedef struct{
    float x, y;

}
//copy lua code
typedef struct {
    uint16_t width;
    uint16_t height;
    const uint8_t* bitmap; // Pointer to the bitmap image data
} GameObject_Image_t;

 
// typedef struct {
//     GameObject_Properties_t properties;
//     GameObject_Image_t image;
// } Space_Object_t;

// Space_Object_t player_ship;

GameObject_t player;
GameObject_t enemies [MAX_ENEMIES];
const char level_map[][];

Camera_t camer={0,0};

volatile bool g_frame_ready=false;


int main(void){

}

//start game loop
volatile bool g_fram_ready=false;


bool AABB_Collision_Detect(const Space_Object_t* obj1, const Space_Object_t* obj2)
{
    // Calculate the coordinates of the bottom-right corner for both objects.
    float obj1_br_x = obj1->properties.x + obj1->image.width;
    float obj1_br_y = obj1->properties.y + obj1->image.height;
    float obj2_br_x = obj2->properties.x + obj2->image.width;
    float obj2_br_y = obj2->properties.y + obj2->image.height;

    // AABB collision check:
    // Collision exists if the rectangles overlap on BOTH the X and Y axes.
    if (obj1->properties.x < obj2_br_x &&
        obj2->properties.x < obj1_br_x &&
        obj1->properties.y < obj2_br_y &&
        obj2->properties.y < obj1_br_y) {
        return true; 
    }

    return false; 
}



void update_game_logic(void){
    //handle player inputs and use adc
    player_ship.properties.x+=player_ship.properties.dx;
    player_ship.properties.y+=player_ship.properties.dy;
}


int main(void){
    
}