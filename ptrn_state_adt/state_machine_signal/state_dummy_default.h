#ifndef STATE_DEFAULT_H
#define STATE_DEFAULT_H

typedef struct SignalState* SignalStatePtr;


// ��������� ������� ���������
typedef struct StateEvents {
	void (*on_entry)(void);
	void (*on_do)(void);
	void (*on_exit)(void);
} StateEvents;

void defaultSignalImplementation(SignalStatePtr s);

#endif
