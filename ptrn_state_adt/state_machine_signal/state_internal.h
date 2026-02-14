#pragma once

// события перехода в каждое состояние
typedef void (*EventUpFunc) (SignalStatePtr, StateEvents);
typedef void (*EventDownFunc) (SignalStatePtr, StateEvents);
typedef void (*EventWaitFunc) (SignalStatePtr, StateEvents);

// внутреннее состояние машины
struct SignalState {
	char* name;
	EventUpFunc up;
	EventDownFunc down;
	EventWaitFunc wait;
};

