#pragma once

// ������� �������� � ������ ���������
typedef void (*EventUpFunc) (SignalStatePtr, StateEvents);
typedef void (*EventDownFunc) (SignalStatePtr, StateEvents);


// ���������� ��������� ������
struct SignalState {
	char* name;
	EventUpFunc up;
	EventDownFunc down;
};

