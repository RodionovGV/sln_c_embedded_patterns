/*

*/
#ifdef __cplusplus
extern "C" {
#endif

#include "logModule.h"

// default states_XXX_default.h
#include "states_semaforo_default.h"
#include "state_pattern.h" // current state
#include "states_semaforo_internal.h" // states_XXX_internal.h

// состояние в которое можем перейти из текущего 
//#include "state_red.h"
#include "state_green.h"

// локальные данные состояния
static TState_Data s_data = {.first_entry = 1,
                      .workStateStartTime = 0,
                      .workTicksState = 0};

static void red_yellow_state(StateSemaforoPtr s, StateSemEvents events){

    // ON_ENTRY
    if (s_data.first_entry) {
        LOG_DBG_TEXT("Red Yellow state ENTER");
        LOG_DBG_TEXT("[ON_ENTRY]");
        if (events.on_entry) {
            events.on_entry();
        }

        s_data.first_entry = 0;
        // get start time
        if (events.check_change_state) {
            //LOG_DBG_TEXT("[DO]");
            s_data.workStateStartTime = events.check_change_state();
        }
    }

    // DO every process state
    if (events.on_do) {
        //LOG_DBG_TEXT("[DO]");
        events.on_do();
    }

    // Transition to another state
    if (events.check_change_state) {
        long currentTime = events.check_change_state();
        long delta = currentTime - s_data.workStateStartTime;
        if (delta > events.workTimeToSwitch) {
            //LOG_DBG_TEXT("NEED TO SWITCH Red");
            //transitionToRed(s);
            LOG_DBG_TEXT("NEED TO SWITCH Green");
            transitionToGreen(s);
            goto exit_from_state;
        }
    }

    if (0) {
        goto exit_from_state;
    }

    return;

exit_from_state:
    LOG_DBG_TEXT("Red Yellow state EXIT");
    init_state(&s_data);
    if (events.on_exit) {
        LOG_DBG_TEXT("[ON_EXIT]");
        events.on_exit();
    }
}

void transitionToRedYellow(StateSemaforoPtr s) {
    LOG_DBG_TEXT("[TRANSITION to Red Yellow]");
    defaultSemaforoImplementation(s);
    s->name = "red_yellow_state";
    s->state_red_yellow = red_yellow_state;
}

#ifdef __cplusplus
}
#endif
