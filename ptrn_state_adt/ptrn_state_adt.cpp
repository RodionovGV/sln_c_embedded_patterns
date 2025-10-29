/*
Метод состояния, реализация с помощью ADT
Abstract data type - абстрактный тип данных.

*/

#include <iostream>

extern "C" {

#include "logModule.h"

#include "state_machine_watch\DigitalStopWatch.h"

#include "state_machine_signal\client_code.h"
}

int main()
{
	std::cout << "Hello World!\n";
	
	DigitalStopWatchPtr w = createWatch();

	for (int i = 0; i < 10; i++) {
		startWatch(w);
		tickWatch(w);
		stopWatch(w);
		tickWatch(w);
		runState(w);
	}

	LOG_INIT("Xample");
	LOG_DBG("Нечего не найдено");


	destroyWatch(w);


	SignalMakerPtr s = createSignal();

	for (int i = 0; i < 400; i++) {
		stateUp(s);
		stateWait(s);
		stateDown(s);
	}

	LOG_DESTROY();

}

