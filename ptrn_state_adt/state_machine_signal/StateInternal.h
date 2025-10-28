#pragma once

// ������� �������� � ������ ���������
typedef void (*EventUpFunc) (SignalStatePtr, StateEvents);
typedef void (*EventDownFunc) (SignalStatePtr, StateEvents);
typedef void (*EventWaitFunc) (SignalStatePtr, StateEvents);

// ���������� ��������� ������
struct SignalState {
	char* name;
	EventUpFunc up;
	EventDownFunc down;
	EventWaitFunc wait;
};

