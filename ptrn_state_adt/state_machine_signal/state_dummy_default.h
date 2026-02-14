#ifndef STATE_DEFAULT_H
#define STATE_DEFAULT_H

typedef struct SignalState* SignalStatePtr;


// Структура событий состояния
typedef struct StateEvents {
	void (*on_entry)(void);
	void (*on_do)(void);
	void (*on_exit)(void);
	int (*check_change_state)(void);
} StateEvents;

void defaultSignalImplementation(SignalStatePtr s);

#endif
