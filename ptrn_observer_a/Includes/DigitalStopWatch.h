#ifndef DIGITAL_STOP_WATCH_H
#define DIGITAL_STOP_WATCH_H

/* 
A pointer to an incomplete type (hides the implementation details). 
Интерфейс к модулю.
*/
typedef struct DigitalStopWatch* DigitalStopWatchPtr;

DigitalStopWatchPtr createDigitalWatch(void);
void destroyDigitalWatch(DigitalStopWatchPtr watch);

long int currentTime(DigitalStopWatchPtr w);

#endif
