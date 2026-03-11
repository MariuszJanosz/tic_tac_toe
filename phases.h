#ifndef PHASES_H
#define PHASES_H

#include "button.h"

#define NUMBER_OF_PHASES 4

typedef enum {
    START_MENU,
    AI_DIFFICULTY_MENU,
    GAME,
    GAME_OVER_MENU
} Phase_id_t;

typedef struct phase_t {
    Phase_id_t phase_id;
    Button_t* buttons;
    int button_count;
} Phase_t;

extern Phase_t* phases;

void init_phases();

#endif //PHASES_H