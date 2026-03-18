#ifndef PHASES_H
#define PHASES_H

#include "button.h"

#define NUMBER_OF_PHASES 5

typedef enum {
    START_MENU,
    AI_SIDE_MENU,
    AI_DIFFICULTY_MENU,
    GAME,
    GAME_OVER_MENU
} Phase_id_t;

typedef struct Animation_t {
    int is_animating;
    unsigned long long time;
    unsigned long long time_elapsed;
} Animation_t;

typedef struct phase_t {
    Phase_id_t phase_id;
    Button_t* buttons;
    int button_count;
    Animation_t* animations;
    int animatin_count;
} Phase_t;

extern Phase_t* phases;

void init_phases();
Button_id_t get_activated_button(Phase_t* phase);

#endif //PHASES_H