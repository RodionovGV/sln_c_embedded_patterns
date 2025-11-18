

#ifndef STATES_SEM_INTERNAL_H
#define STATES_SEM_INTERNAL_H

//#ifdef __cplusplus
//extern "C" {
//#endif

// StateEvents из default - структура событий в State
typedef void (*StateYellowFxn)(StateSemaforoPtr, StateSemEvents);
typedef void (*StateRedFxn)(StateSemaforoPtr, StateSemEvents);
typedef void (*StateRedYellowFxn)(StateSemaforoPtr, StateSemEvents);
typedef void (*StateGreenFxn)(StateSemaforoPtr, StateSemEvents);
typedef void (*StateGreenBlinkFxn)(StateSemaforoPtr, StateSemEvents);

// скрытая структура от пользователя
struct StateSemaforo {
    char* name;
    int liveTime;
    int liveTimeInState;
    StateYellowFxn state_yellow;
    StateRedFxn state_red;
    StateRedYellowFxn state_red_yellow;
    StateGreenFxn state_green;
    StateGreenBlinkFxn state_green_blink;
};

// per state
typedef struct {
    int first_entry; // флаг первого вхождения при начале работы в этом состоянии
    long workStateStartTime; //
    long workTicksState;
} TState_Data;

// обнуление состояния при выходе
static void init_state(TState_Data* s) {
    s->first_entry = 1;
    s->workStateStartTime = 0;
    s->workTicksState = 0;
}
//#ifdef __cplusplus
//}
//#endif

#endif /* STATES_SEM_INTERNAL_H */
