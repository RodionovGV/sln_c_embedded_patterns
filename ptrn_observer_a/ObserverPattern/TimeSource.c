/*
Источник данных. Тут нужно подписыватья на обновления данных.

*/
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SystemTime.h"
#include "TimeSubject.h"

static SystemTime currentTime = { 0 };
/*
 Dummy stubs for the invoked functions:
 */
static SystemTime calculateNewTime(void) {

    currentTime.theTime++;

    /* Time will pass slowly in this watch... */
    SystemTime newTime = currentTime;

    return newTime;
}

/* Implementation of the original responsibility of the
   TimeSource (code for initialization, etc omitted). */
static void msTick() {
    
    SystemTime currentTime = calculateNewTime();

	updateDataObservers(&currentTime);
}

void stepTime() {
    msTick();
}
