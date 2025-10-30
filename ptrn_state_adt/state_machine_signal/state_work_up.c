#include <stdio.h>

#include "logModule.h"

#include "state_dummy_default.h"
#include "state_work_up.h"
#include "state_internal.h"

// cohesive state
#include "state_work_down.h"

static void up_state(SignalStatePtr s, StateEvents events){
	static int first_entry = 1;

	static long value;

	// ON_ENTRY
	if (first_entry && events.on_entry) {
		LOG_DBG_TEXT("[UP ON_ENTRY]");
		events.on_entry();
		first_entry = 0;
	}

	// DO
	if (events.on_do) {
		LOG_DBG_TEXT("[UP DO]");
		events.on_do();
	}

	// Выход по счётчику
	value += 1; //++(*signal);

	// ON_EXIT
	if (value > 10) {
		transitionToDown(s);
		if (events.on_exit) events.on_exit();
		value = 0;
		first_entry = 1;
		goto exit_from_state;
	}

exit_from_state:
	if (events.on_exit) {
		LOG_DBG_TEXT("[UP ON_EXIT]");
		events.on_exit();
	}
}

void transitionToUp(SignalStatePtr s) {
	LOG_DBG_TEXT("[TRANSITION to UP]");
	defaultSignalImplementation(s);
	s->name = "Up";
	s->up = up_state;

	//s->signal = 0; // start from zero
	// entry to up_state
}