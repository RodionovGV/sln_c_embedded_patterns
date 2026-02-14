#ifndef TIME_SUBJECT_H
#define TIME_SUBJECT_H

#include "SystemTime.h"
#include "TimeObserver.h"

void updateDataObservers(SystemTime* currentTime);

void attach(const TimeObserver* observer); 

void detach(const TimeObserver* observer);

#endif
