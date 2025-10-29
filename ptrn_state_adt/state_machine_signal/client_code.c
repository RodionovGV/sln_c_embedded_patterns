#include <stdlib.h> // NULL, malloc

#include "logModule.h"

#include "client_code.h"
#include "StateInternal.h"

// cohensive state
#include "StateUp.h"

//
#include "lamp_driver.h"

struct SignalMaker {
	struct SignalState state;
};

SignalMakerPtr createSignal(void) {
	LOG_DBG("RUN: createSignal");
	SignalMakerPtr instance = malloc(sizeof * instance);

	createLampDriver();

	if (NULL != instance) {
		transitionToUp(&instance->state);
	}
	return instance;
}

void destroySignal(SignalMakerPtr instance) {
	LOG_DBG("RUN: destroySignal");
	free(instance);
	destroyLampDriver();
}

void stateUp(SignalMakerPtr instance)
{
	LOG_DBG("RUN: stateUp");
	StateEvents events = {
	.on_entry = turnOnLamp,
	.on_do = NULL,
	.on_exit = NULL 
	};

	instance->state.up(&instance->state, events);
}

void stateWait(SignalMakerPtr instance)
{
	StateEvents events = {
	.on_entry = turnWaitLamp,
	.on_do = NULL,
	.on_exit = NULL,
	.check_change_state = NULL
	};

	instance->state.wait(&instance->state, events);
}


void stateDown(SignalMakerPtr instance)
{
	StateEvents events = {
	.on_entry = turnOffLamp,
	.on_do = NULL,
	.on_exit = NULL,
	.check_change_state = turnWaitLamp
	};

	instance->state.down(&instance->state, events);
}
