
#include "TUM_Draw.h"

#include "my_structs.h"
#include "alien.h"

bullet_t *BulletInit() {
    bullet_t *my_bullet = pvPortMalloc(sizeof(bullet_t));
    my_bullet->position.x = 0;
    my_bullet->position.y = 0;
    my_bullet->active = BULLET_PASSIVE;
    my_bullet->lock = xSemaphoreCreateMutex(); // Locking mechanism

    return my_bullet;
}

spaceship_t *SpaceShipInit() {
    spaceship_t *my_spaceship = pvPortMalloc(sizeof(spaceship_t));
    int x = 0;
    x = SCREEN_WIDTH / 2 - SHIP_WIDTH / 2;
    my_spaceship->x_position = x;
    my_spaceship->lifes = PLAYER_LIFES;
    my_spaceship->lock = xSemaphoreCreateMutex(); // Locking mechanism

    return my_spaceship;
}

alien_t *AlienInit(int alien_score) {
    alien_t *my_alien = pvPortMalloc(sizeof(alien_t));
    my_alien->position.x = ALIEN_START_X;
    my_alien->position.y = ALIEN_START_Y;
    my_alien->alien_score = alien_score;
    my_alien->active = BULLET_ACTIVE;  // init to active because it should be display from the beginning
    my_alien->img_h = AlienLoadImg(alien_score);
    my_alien->lock = xSemaphoreCreateMutex(); // Locking mechanism
    return my_alien;
}

alien_t **AlienInitColumn(int x_position) {
    // initialize a column with 5 aliens and return the pointer to the first object.
    alien_t **column = pvPortMalloc(sizeof(alien_t) * ALIENS_PER_COLUMN);

    column[0] = AlienInit(ALIEN_HARD);
    column[1] = AlienInit(ALIEN_MIDDLE);
    column[2] = AlienInit(ALIEN_MIDDLE);
    column[3] = AlienInit(ALIEN_EASY);
    column[4] = AlienInit(ALIEN_EASY);

    for (int i = 0; i < ALIENS_PER_COLUMN; i++) {
        column[i]->position.x = x_position;
        column[i]->position.y += (ALIEN_WIDTH + ALIEN_PADDING_Y) * i;
    }
    return column;

}

alien_t ***AlienInitMatrix() {
    alien_t ***row = pvPortMalloc(sizeof(alien_t) * ALIENS_PER_ROW);
    for (int i = 0; i < ALIENS_PER_ROW; i++) {  //sizeof(row) / sizeof(alien_t)
        row[i] = AlienInitColumn(ALIEN_START_Y + (ALIEN_WIDTH + ALIEN_PADDING_X) * i);
    }
    return row;
}

game_objects_t *game_objects_init() {
    game_objects_t *game_objects = pvPortMalloc(sizeof(game_objects_t));
    game_objects->my_spaceship = SpaceShipInit();
    game_objects->my_bullet = BulletInit(); 
    //game_objects->my_alien = AlienInit(ALIEN_EASY);   
    //alien_t *column = AlienInitColumn();
    //game_objects->alien_column_start = AlienInitColumn();
    game_objects->alien_matrix = AlienInitMatrix();
    return game_objects;
}