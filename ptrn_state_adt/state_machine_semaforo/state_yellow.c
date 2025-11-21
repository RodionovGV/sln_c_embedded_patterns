/*

*/
#ifdef __cplusplus
extern "C" {
#endif

#include "logModule.h"

#include "states_semaforo_default.h"
#include "state_yellow.h"
#include "states_semaforo_internal.h"


// cohesive state
#include "state_red.h"

static TState_Data s_data = {.first_entry = 1,
                      .workStateStartTime = 0,
                      .workTicksState = 0};

static void yellow_state(StateSemaforoPtr s, StateSemEvents events){

    // ON_ENTRY
    if (s_data.first_entry) {
        LOG_DBG_TEXT("Yellow state ENTER");
        LOG_DBG_TEXT("[ON_ENTRY]");
        if (events.on_entry) {
            events.on_entry();
        }

        s_data.first_entry = 0;
        // get start time
        if (events.check_change_state) {
            //LOG_DBG_TEXT("[UP DO]");
            //long startTime = events.check_change_state();
            //s_data.workStateStartTime = startTime;
            s_data.workStateStartTime = events.check_change_state();
        }
    }

    // DO
    if (events.on_do) {
        //LOG_DBG_TEXT("[UP DO]");
        events.on_do();
    }

    if (events.check_change_state) {
        long currentTime = events.check_change_state();
        long delta = currentTime - s_data.workStateStartTime;
        if (delta > events.workTimeToSwitch) {
            LOG_DBG_TEXT("NEED TO SWITCH RED");
            transitionToRed(s);
            goto exit_from_state;
        }
    }

    if (0) {
        goto exit_from_state;
    }

    return;

exit_from_state:
    LOG_DBG_TEXT("Yellow state EXIT");
    // reset state
    init_state(&s_data);
    if (events.on_exit) {
        LOG_DBG_TEXT("[ON_EXIT]");
        events.on_exit();
    }
}

void transitionToYellow(StateSemaforoPtr s) {
    LOG_DBG_TEXT("[TRANSITION to yellow_state]");
    defaultSemaforoImplementation(s);
    s->name = "yellow_state";
    s->state_yellow = yellow_state;
}

#ifdef __cplusplus
}
#endif
