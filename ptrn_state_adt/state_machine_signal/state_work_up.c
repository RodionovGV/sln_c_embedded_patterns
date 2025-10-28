#include <stdio.h>

#include "state_dummy_default.h"
#include "StateUp.h"
#include "StateInternal.h"

// cohesive state
#include "StateDown.h"

static void up_state(SignalStatePtr s, StateEvents events){
	static int first_entry = 1;

	static long value;

	// ON_ENTRY
	if (first_entry && events.on_entry) {
		printf("Down state - ONENTRY: ");
		events.on_entry();
		first_entry = 0;
	}

	// DO
	if (events.on_do) events.on_do();

	value += 1; //++(*signal);

	// ON_EXIT
	if (value > 10) {
		transitionToDown(s);
		if (events.on_exit) events.on_exit();
		first_entry = 1;
	}
}

void transitionToUp(SignalStatePtr s) {
	defaultSignalImplementation(s);
	s->name = "Up";
	s->up = up_state;

	//s->signal = 0; // start from zero
	// entry to up_state
}