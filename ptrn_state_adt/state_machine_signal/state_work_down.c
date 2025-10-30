#include <stdio.h>

#include "logModule.h"

#include "state_dummy_default.h"
#include "state_internal.h"

#include "state_work_down.h"

// cohensive state
#include "state_work_up.h"
#include "state_work_wait.h"

static void down_state(SignalStatePtr s, StateEvents events){
	static int first_entry = 1;

	// ON_ENTRY
	if (first_entry && events.on_entry) {
		LOG_DBG_TEXT("[DOWN ON_ENTRY]");
		events.on_entry();
		first_entry = 0;
	}

	// DO
	if (events.on_do) {
		LOG_DBG_TEXT("[DOWN DO]");
		events.on_do();
	}

	// Приоритизация выхода. Или или.
	// 
	// DO
	if (events.check_change_state) {
		LOG_DBG_TEXT("[DOWN CHANGE_STATE]");
		int result = events.check_change_state();
		if (result) {
			transitionToWait(s);
		};
		goto exit1_from_state;
	}

	// ON_EXIT
	transitionToUp(s);

	//events.on_exit();
exit1_from_state:
	if (events.on_exit) {
		events.on_exit();
	}

	
}

void transitionToDown(SignalStatePtr s) {
	LOG_DBG_TEXT("[TRANSITION to DOWN]");
	defaultSignalImplementation(s);
	s->name = "Down";
	s->down = down_state;
}

