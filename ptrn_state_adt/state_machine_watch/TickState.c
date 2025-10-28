// Tick state

#include "TickState.h"
#include "WatchStateInternal.h"

/* Possible transition to the following state: */
#include "StoppedState.h"

static void tickWatch(WatchStatePtr state)
{
    int Tick = 0;
    for (;;) {
        Tick++;
        if (Tick > 5) {
            transitionToStopped(state);
            break;
        }

    }
}

void transitionToTick(WatchStatePtr state)
{
    /* Initialize with the default implementation before
       specifying the events to be handled in the started
       state. */
    defaultImplementation(state);
    state->name = "Tick";
    state->tick = tickWatch;
}

