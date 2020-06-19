#include <time.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include "TUM_Draw.h"

#include "spaceship.h"

#define SCREEN_FREQUENCY    1000/60

void vManageScreenTask(void *pvParameters){

    printf("Init Manage Screen");

    // init vars to update screen and call this task every .. milliseconds
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = SCREEN_FREQUENCY;
    //int framerate = 0;
    //char framerate_text[50];
    //time_t lastWakeTime = clock();  

    // init spaceship
    struct spaceship_t *my_spaceship = {0};



    

    

    // Needed such that Gfx library knows which thread controlls drawing
    // Only one thread can call tumDrawUpdateScreen while and thread can call
    // the drawing functions to draw objects. This is a limitation of the SDL
    // backend.
    tumDrawBindThread();

    xLastWakeTime = xTaskGetTickCount(); // Initialise the xLastWakeTime variable with the current time.

    while(1) {  //TODO: change this to while the screen is active
        vTaskDelayUntil( &xLastWakeTime, xFrequency );  // start this task every xFrequency millisecond
        tumDrawClear(Black); // Clear screen

        SpaceShipDraw(my_spaceship)

        tumDrawUpdateScreen();
    }
    vTaskDelete(NULL); 
}