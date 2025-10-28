// State Stopped
#include "StoppedState.h"
#include "WatchStateInternal.h"

/* Possible transition to the following state: */
#include "StartedState.h"

static void startWatch_state(WatchStatePtr state) 
{
  transitionToStarted(state);
}

void transitionToStopped(WatchStatePtr state) 
{
  /* Initialize with the default implementation before
     specifying the events to be handled in the stopped
     state. */
  defaultImplementation(state);
  state->name = "Stopped";
  state->start = startWatch_state;
}
