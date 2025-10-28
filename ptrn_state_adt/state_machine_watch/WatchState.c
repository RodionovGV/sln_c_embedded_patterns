// Transition description
// Функции заглушки для того, чтобы ничего не делать в состоянии
// если не находимся в этом состоянии
#include <stdio.h>

#include "WatchState.h"
#include "WatchStateInternal.h"

/*
Provide the default implementations:
*/

static void defaultStop(WatchStatePtr state) 
{
  /* We'll get here if the stop event isn't supported
     in the concrete state. */
    printf("Event 'start' is not supported in this state.\n");
}

static void defaultStart(WatchStatePtr state) 
{
    /* We'll get here if the start event isn't supported
       in the concrete state. */
}

static void defaultFxn(WatchStatePtr state) {

}

static void defaultTick(WatchStatePtr state) {

}

void defaultImplementation(WatchStatePtr state) {
    state->start = defaultStart;
    state->stop = defaultStop;
    state->fxn = defaultFxn;
    state->tick = defaultTick;
}
