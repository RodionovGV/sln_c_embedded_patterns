/*

*/
#ifdef __cplusplus
extern "C" {
#endif

#include "states_semaforo_default.h"
#include "states_semaforo_internal.h"

static void defaultYellow(StateSemaforoPtr s, StateSemEvents events) {

}

static void defaultRed(StateSemaforoPtr s, StateSemEvents events) {

}

static void defaultRedYellow(StateSemaforoPtr s, StateSemEvents events) {

}

static void defaultGreen(StateSemaforoPtr s, StateSemEvents events) {

}

static void defaultGreenBlink(StateSemaforoPtr s, StateSemEvents events) {

}

static void defaultYellowBlink(StateSemaforoPtr s, StateSemEvents events) {

}

void defaultSemaforoImplementation(StateSemaforoPtr s, StateSemEvents events) {
	s->state_yellow = defaultYellow;
	s->state_red = defaultRed;
	s->state_red_yellow= defaultRedYellow;
	s->state_green = defaultGreen;
	s->state_green_blink = defaultGreenBlink;
	s->state_yellow_blink = defaultYellowBlink;
}

#ifdef __cplusplus
}
#endif
