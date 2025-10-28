#include <stdio.h>

#include "state_dummy_default.h"
#include "StateInternal.h"

#include "StateDown.h"

// cohensive state
#include "StateUp.h"
#include "state_work_wait.h"

static void down_state(SignalStatePtr s, StateEvents events){
	static int first_entry = 1;

	// ON_ENTRY
	if (first_entry && events.on_entry) {
		printf("Down state - ONENTRY: ");
		events.on_entry();
		first_entry = 0;
	}

	// DO
	if (events.on_do) events.on_do();

	// Приоритизация выхода. Или или.
	// 
	// DO
	if (events.check_change_state) {
		int result = events.check_change_state();
		if (result) {
			transitionToWait(s);
		};
	}

	// ON_EXIT
	transitionToUp(s);

	//events.on_exit();
}

void transitionToDown(SignalStatePtr s) {
	defaultSignalImplementation(s);
	s->name = "Down";
	s->down = down_state;
}

