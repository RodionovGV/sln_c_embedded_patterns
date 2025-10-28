#pragma once

typedef struct SignalMaker* SignalMakerPtr;


SignalMakerPtr createSignal(void);

void destroySignal(SignalMakerPtr);

// �������� ���� ���������
// ��������� ����� ���� �����������?
void stateUp(SignalMakerPtr instance);
void stateDown(SignalMakerPtr instance);
