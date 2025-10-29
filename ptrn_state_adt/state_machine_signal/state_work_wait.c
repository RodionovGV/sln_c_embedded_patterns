#include <stdio.h>

#include "logModule.h"

#include "state_dummy_default.h"
#include "StateInternal.h"

#include "state_work_wait.h"

// cohesive state
#include "StateUp.h"

static void up_wait(SignalStatePtr s, StateEvents events){
	static int first_entry = 1;

	static long value;

	// ON_ENTRY
	if (first_entry && events.on_entry) {
		LOG_DBG("WAIT ON_ENTRY");
		printf("Wait state - ONENTRY: ");
		events.on_entry();
		first_entry = 0;
	}

	// DO
	if (events.on_do) {
		LOG_DBG("WAIT DO");
		events.on_do();
	}

	value += 1; 

	// ON_EXIT
	if (value > 10) {
		LOG_DBG("WAIT ON_EXIT");
		events.on_do();
		transitionToUp(s);
		if (events.on_exit) events.on_exit();
		first_entry = 1;
	}
}

void transitionToWait(SignalStatePtr s) {
	defaultSignalImplementation(s);
	s->name = "Wait";
	s->down = up_wait;
}