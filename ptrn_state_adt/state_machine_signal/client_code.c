#include <stdlib.h> // NULL, malloc

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
	SignalMakerPtr instance = malloc(sizeof * instance);

	createLampDriver();


	if (NULL != instance) {
		transitionToUp(&instance->state);
	}
	return instance;
}

void destroySignal(SignalMakerPtr instance) {
	free(instance);
	destroyLampDriver();
}

void stateUp(SignalMakerPtr instance)
{
	StateEvents events = {
	.on_entry = turnOnLamp,
	.on_do = NULL,
	.on_exit = NULL 
	};

	instance->state.up(&instance->state, events);
}

void stateDown(SignalMakerPtr instance)
{
	StateEvents events = {
	.on_entry = turnOffLamp,
	.on_do = NULL,
	.on_exit = NULL
	};
	instance->state.down(&instance->state, events);
}
