#pragma once

typedef struct SignalMaker* SignalMakerPtr;


SignalMakerPtr createSignal(void);

void destroySignal(SignalMakerPtr);

// Перечень всех состояний
// Состояния могут быть внутренними?
void stateUp(SignalMakerPtr instance);
void stateDown(SignalMakerPtr instance);
void stateWait(SignalMakerPtr instance);


void runStateMachine(SignalMakerPtr instance);
