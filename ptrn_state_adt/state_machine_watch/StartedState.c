// State Started 
/*
entry / entry Acitvity
do / doActivity
exit / exitActivity
*/
#include "StartedState.h"
#include "WatchStateInternal.h"

/* Possible transition to the following state: */
#include "StoppedState.h"
#include "TickState.h"

static void stopWatch_state(WatchStatePtr state) 
{
    //transitionToStopped(state);
    transitionToTick(state);
    state->fxn(state);
}

void transitionToStarted(WatchStatePtr state) 
{
   /* Initialize with the default implementation before
      specifying the events to be handled in the started
      state. */
   defaultImplementation(state);
   state->name = "Started";
   state->stop = stopWatch_state;
   state->fxn = stopWatch_state;
}

