#include <stdio.h>

#include "state_dummy_default.h"
#include "StateInternal.h"

static void defaultUp(SignalStatePtr s) {

}

static void defaultDown(SignalStatePtr s) {

}

// Для каждого состояния нужно провисать default
void defaultSignalImplementation(SignalStatePtr s) {
	s->down = defaultDown;
	s->up = defaultUp;
}