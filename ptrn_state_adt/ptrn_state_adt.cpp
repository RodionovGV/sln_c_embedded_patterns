/*
Метод состояния, реализация с помощью ADT
Abstract data type - абстрактный тип данных.

*/

#include <iostream>

extern "C" {

#include <slog.h>

#include "state_machine_watch\DigitalStopWatch.h"

#include "state_machine_signal\client_code.h"
}
void greet()
{
	/* Get and print slog version */
	slog("=========================================");
	slog("SLog Version: %s", slog_version(0));
	slog("=========================================");
}

int main()
{
	std::cout << "Hello World!\n";
	
	/* Used variables */
	slog_config_t cfg;
	int nInteger = 69;
	char sBuffer[14];

	snprintf(sBuffer, sizeof(sBuffer), "test string");
	//uint16_t nLogFlags = SLOG_ERROR | SLOG_NOTAG | SLOG_NOTE;

	/* Initialize slog and allow only error and not tagged output */
	slog_init("example", SLOG_FLAGS_ALL, 0);
	slog_config_get(&cfg);
	cfg.nToFile = 1;
	slog_config_set(&cfg);
	/* Greet users */
	greet();


	DigitalStopWatchPtr w = createWatch();

	for (int i = 0; i < 10; i++) {
		startWatch(w);
		tickWatch(w);
		stopWatch(w);
		tickWatch(w);
		runState(w);
	}

	destroyWatch(w);


	SignalMakerPtr s = createSignal();

	for (int i = 0; i < 400; i++) {
		stateUp(s);
		stateWait(s);
		stateDown(s);
	}
	slog_destroy();

}

