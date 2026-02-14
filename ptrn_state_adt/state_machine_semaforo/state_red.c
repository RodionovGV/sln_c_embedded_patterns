/*

*/
#ifdef __cplusplus
extern "C" {
#endif

#include "logModule.h"

#include "states_semaforo_default.h"
#include "state_red.h"
#include "states_semaforo_internal.h"


// cohesive state
// red
//#include "state_yellow.h"
#include "state_red_yellow.h"

// локальные данные состояния
static TState_Data s_data = { .first_entry = 1,
                      .workStateStartTime = 0,
                      .workTicksState = 0 };

static void red_state(StateSemaforoPtr s, StateSemEvents events){

	// ON_ENTRY
	if (s_data.first_entry) {
        LOG_DBG_TEXT("Red state ENTER");
		LOG_DBG_TEXT("[ON_ENTRY]");
		if (events.on_entry) {
			events.on_entry();
		}

		s_data.first_entry = 0;
		// get start time
		if (events.check_change_state) {
			//LOG_DBG_TEXT("[UP DO]");
			s_data.workStateStartTime = events.check_change_state();
		}
	}

	// DO
	if (events.on_do) {
		//LOG_DBG_TEXT("[UP DO]");
		events.on_do();
	}

	if (events.check_change_state) {
		//LOG_DBG_TEXT("[UP DO]");
		long currentTime = events.check_change_state();
		long delta = currentTime - s_data.workStateStartTime;
		if (delta > events.workTimeToSwitch) {
			//LOG_DBG_TEXT("NEED TO SWITCH Yellow");
			//transitionToYellow(s);
			LOG_DBG_TEXT("NEED TO SWITCH Red Yellow");
			transitionToRedYellow(s);
			goto exit_from_state;
		}
	}

	if (0) {
		goto exit_from_state;
	}
	
	return; // выходим

	// выполняется только при выходе из состояния
exit_from_state:
    LOG_DBG_TEXT("Red state EXIT");
    init_state(&s_data);
	if (events.on_exit) {
		LOG_DBG_TEXT("[ON_EXIT]");
		events.on_exit();
	}
}

void transitionToRed(StateSemaforoPtr s) {
	LOG_DBG_TEXT("[TRANSITION to Red]");
	defaultSemaforoImplementation(s);
	s->name = "red_state";
	s->state_red = red_state;
}

#ifdef __cplusplus
}
#endif
