#include <stdio.h>

#include "logModule.h"

#include "state_dummy_default.h"
#include "state_internal.h"

#include "state_work_wait.h"

// cohesive state
#include "state_work_up.h"

static void up_wait(SignalStatePtr s, StateEvents events){
	static int first_entry = 1;

	static long value;

	// ON_ENTRY
	if (first_entry && events.on_entry) {
		LOG_DBG_TEXT("WAIT ON_ENTRY");
		events.on_entry();
		first_entry = 0;
	}

	// DO
	if (events.on_do) {
		LOG_DBG_TEXT("WAIT DO");
		events.on_do();
	}

	value += 1; 

	// ON_EXIT
	if (value > 10) {
		LOG_DBG_TEXT("WAIT ON_EXIT");
		transitionToUp(s);
		first_entry = 1;
		goto exit_from_state;
	}

exit_from_state:
	if (events.on_exit) {
		LOG_DBG_TEXT("[WAIT ON_EXIT]");
		events.on_exit();
	}
}

void transitionToWait(SignalStatePtr s) {
	LOG_DBG_TEXT("[TRANSITION to WAIT]");
	defaultSignalImplementation(s);
	s->name = "Wait";
	s->wait = up_wait; 
}