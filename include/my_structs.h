#include "TUM_Draw.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#ifndef TEST_MYSTRUCTS_H

#define TEST_MYSTRUCTS_H  

#define	EXIT_FAILURE	1	/* Failing exit status.  */
#define	EXIT_SUCCESS	0	/* Successful exit status.  */

#define mainGENERIC_PRIORITY (tskIDLE_PRIORITY)
#define mainGENERIC_STACK_SIZE ((unsigned short)2560)

#define SCREEN_FREQUENCY    1000/60

#define PADDING         10

#define BULLET_HEIGHT   5
#define BULLET_WIDTH    2
#define OBJ_ACTIVE      1
#define OBJ_PASSIVE     0
#define BULLET_SPEED    7

#define SHIP_HEIGHT     10
#define SHIP_WIDTH      50
#define GUN_HEIGHT      10
#define GUN_WIDHT       10
#define SHIP_SPEED      5
#define SHIP_X_MAX      SCREEN_WIDTH - PADDING- SHIP_WIDTH / 2
#define SHIP_X_MIN      PADDING + SHIP_WIDTH / 2
#define SHIP_Y_CO       SCREEN_HEIGHT - PADDING - SHIP_HEIGHT

#define PLAYER_LIFES    2  // Player lifes besides the first one
#define LEVEL_SPEED_INCREASE_FAKTOR     2

#define ALIEN_EASY      10
#define ALIEN_MIDDLE    20    
#define ALIEN_HARD      30
#define ALIENS_PER_ROW  8
#define ALIENS_PER_COLUMN   5
#define ALIEN_WIDTH     35
#define ALIEN_PADDING_X 25
#define ALIEN_PADDING_Y 10
#define ALIEN_START_X   50
#define ALIEN_START_Y   50
#define ALIEN_MIN_X     20
#define ALIEN_MAX_X     SCREEN_WIDTH - ALIEN_MIN_X
#define ALIEN_X_SPEED   0.3
#define ALIEN_ACCELERATION      0.05
#define ALIEN_Y_SPEED   5

#define MAX_ACTIVE_ALIEN_BULLETS    10
#define ALIEN_BULLET_SPEED  3
#define RAND_SHOOT_CHANCE   1000  // 1 in RANDOM_SHOOT_CHANCE

#define NUMBER_OF_BUNKERS   5
#define BUNKER_CELL_SIZE    7
#define BUNKER_X_CELLS_NUMBER 7
#define BUNKER_POSITION_Y   SCREEN_HEIGHT - SHIP_HEIGHT - GUN_HEIGHT - 3 * BUNKER_CELL_SIZE - 2 * PADDING


typedef struct{
    coord_t position;
    int active;
    SemaphoreHandle_t lock;
}bullet_t;

typedef struct{
    bullet_t **first_bullet;
    SemaphoreHandle_t lock;
}alien_bullet_t;


typedef struct{
    coord_t position;
    int lifes;
    SemaphoreHandle_t lock;
}spaceship_t;

typedef struct {
    float x;
    float y;
}coord_float_t;

typedef struct {
    coord_float_t position;  // using float to also keep track of position changes smaller then one pixel -> move every n screen ticks
    int alien_score;
    int active;
    image_handle_t img_h;
    SemaphoreHandle_t lock;   
}alien_t;

typedef struct {
    alien_t **first_alien; // pointer to the pointer of the first alien in the column
    int lowest_active_alien;  // the number of the lowest(on screen) alien in this column (needed to see which alien can shoot).
    int *active_aliens;  //array with an entry for each alien. 1 if alien is active, else 0
    int active;
    SemaphoreHandle_t lock;
}alien_column_t;

typedef struct{
    alien_column_t **first_column;  
    int *active_columns;  //array with an entry for each column. 1 if column is active, else 0
    int leftest_active_column;  // the number of the most left column (needed to move the aliens always right to the side)
    int rightest_active_column;  // the number of the most right column (needed to move the aliens always right to the side)
    SemaphoreHandle_t lock;
}alien_matrix_t;

typedef struct{
    int current_score;
    int highscore;
    int level;
    int lifes_left;
    SemaphoreHandle_t lock;
}score_t;

typedef struct{
    int active;
    coord_t position;  // the middle of the bunker. 
    int width;
}bunker_cell_t;


typedef struct{
    /*
    a bunker that has the following shape.
    each # stands for one cell that can be destroyed individually.

    #####
    #   #
    #####

    each row is represented as an array of cells. 
    The value of row is the pointer to the first element in this row.

    */
    coord_t position;
    bunker_cell_t *upper_row;
    bunker_cell_t *middle_row;  // has three inactive cells in the middle
    bunker_cell_t *lower_row;
    SemaphoreHandle_t lock;
}bunker_t;


typedef struct {
    /* a single object which holds pointers to all the other obejcts.
    
    is mainly used to be passed to the different tasks so that every task can access all the information.
    */
    spaceship_t *my_spaceship;
    bullet_t *my_bullet;
    bullet_t **alien_bullets;
    alien_matrix_t *alien_matrix;  //first_row->first_column = first_alien; starting at top left of screen
    bunker_t **bunkers;  // pointer to the first bunker
    score_t *score;
    SemaphoreHandle_t lock;
} game_objects_t;

typedef struct {
    TaskHandle_t *tasks;
    int length;
}taskhandle_array_t;

typedef struct{
    /* a datatype to be passed to the manage button tasks so it has access to all the taskshandles and the game_objects*/
    game_objects_t *game_objects;
    taskhandle_array_t *game_task_handlers;
}tasks_and_game_objects_t;


alien_matrix_t *AlienInitMatrix();
game_objects_t *game_objects_init();

#endif /*TEST_MYSTRUCTS_H*/