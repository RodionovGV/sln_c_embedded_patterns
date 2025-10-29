#include <stdlib.h> // NULL, malloc

#include "client_code.h"
//#include "StateInternal.h"

// cohensive state
#include "StateUp.h"

//
#include "lamp_driver.h"

// context
struct SignalMaker {
	//SignalState state;
	SignalMakerPtr state;
	StateEvents events;
	// указатель на лампу?
};

void changeState(SignalMakerPtr instance, StateEvents events,  SignalStatePtr newState) {
	// Смена состояний через эту функцию.
	instance->state = newState;
	instance->events = events;
}

SignalMakerPtr createSignal(void) {
	SignalMakerPtr instance = malloc(sizeof * instance);
	

	createLampDriver();

	if (NULL != instance) {
		//transitionToUp(&instance->state);
		StateEvents events = {
		.on_entry = turnOnLamp,
		.on_do = NULL,
		.on_exit = NULL
		};
		changeState(instance, events, transitionToUp());
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

	//instance->state.up(&instance->state, events);
	//changeState();
}

void stateWait(SignalMakerPtr instance)
{
	StateEvents events = {
	.on_entry = turnWaitLamp,
	.on_do = NULL,
	.on_exit = NULL,
	.check_change_state = NULL
	};

	//instance->state.wait(&instance->state, events);
	
}


void stateDown(SignalMakerPtr instance)
{
	StateEvents events = {
	.on_entry = turnOffLamp,
	.on_do = NULL,
	.on_exit = NULL,
	.check_change_state = turnWaitLamp
	};

	//instance->state.down(&instance->state, events);
}


void runStateMachine(SignalMakerPtr instance) {
	instance->state(instance);
}
