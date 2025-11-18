/*

✅yellow
✅red
✅red+yellow
✅green
✅green_blink
    circle
*/
//#ifdef __cplusplus
//extern "C" {
//#endif

/* Standard Header files */
#define _CRT_SECURE_NO_WARNINGS // чтобы работал sprintf
#include <stdio.h>   // for sprintf
#include <windows.h> // for Sleep

#include "logModule.h"
#include "states_semaforo_implement.h"
#include "states_semaforo_internal.h"

// cohesive state
#include "state_yellow.h"

struct SemaforoMaker {
    long tickTimeWork;
	struct StateSemaforo state;
};
SemaforoMakerPtr _instance = NULL;

SemaforoMakerPtr createSemaforo(void){
    SemaforoMakerPtr instance = malloc(sizeof * instance);
    // TODO:
    // time now init
    // 
    if (NULL != instance){
        _instance = instance;
        instance->tickTimeWork = 0;
        transitionToYellow(&instance->state);
    }
    LOG_DBG_TEXT("SEMAFORO CREATE");

    return instance;
}

void destroySemaforo(SemaforoMakerPtr instance){
    free(instance);
    LOG_DBG_TEXT("SEMAFORO DESTROY");
}

long getWorkTicks() {
    long retval = -1;
    if (NULL != _instance) {
		retval = _instance->tickTimeWork;
    }
    return retval;
}

void stateYellow(SemaforoMakerPtr instance){
    StateSemEvents events = {
    .on_entry = NULL, // по on_entry запускать время работы в состоянии, чтобы было точно
    .on_do = NULL,
    .on_exit = NULL,
    .workTimeToSwitch = 3L, // tics
    .check_change_state = getWorkTicks
	};
    instance->state.state_yellow(&instance->state, events);
}

void stateRed(SemaforoMakerPtr instance) {
    StateSemEvents events = {
    .on_entry = NULL,
    .on_do = NULL,
    .on_exit = NULL,
    .workTimeToSwitch = 15L, // tics
    .check_change_state = getWorkTicks
    };
    instance->state.state_red(&instance->state, events);
}

void stateRedYellow(SemaforoMakerPtr instance) {
    StateSemEvents events = {
    .on_entry = NULL,
    .on_do = NULL,
    .on_exit = NULL,
    .workTimeToSwitch = 3L, // tics
    .check_change_state = getWorkTicks
    };
    instance->state.state_red_yellow(&instance->state, events);
}

void stateGreen(SemaforoMakerPtr instance) {
    StateSemEvents events = {
    .on_entry = NULL,
    .on_do = NULL,
    .on_exit = NULL,
    .workTimeToSwitch = 10L, // tics
    .check_change_state = getWorkTicks
    };
    instance->state.state_green(&instance->state, events);
}

void stateGreenBlink(SemaforoMakerPtr instance) {
    StateSemEvents events = {
    .on_entry = NULL,
    .on_do = NULL,
    .on_exit = NULL,
    .workTimeToSwitch = 3L, // tics
    .check_change_state = getWorkTicks
    };
    instance->state.state_green_blink(&instance->state, events);
}

void semaforo_stae_mashine(SemaforoMakerPtr instance) {
    char dbg_msg[200];
    sprintf(dbg_msg, "Current state: %s", instance->state.name);
    LOG_DBG_TEXT(dbg_msg);

    // Circle state machine
    for (int i = 0; i < 100; i++) {
        instance->tickTimeWork++;

		stateYellow(instance);
        stateRed(instance);
        stateRedYellow(instance);
        stateGreen(instance);
        stateGreenBlink(instance);
		
        Sleep(1000); // пауза

		sprintf(dbg_msg, "Current state: %s, tick work: %12ld", 
                instance->state.name, instance->tickTimeWork);
        //LOG_DBG_PROGRESS(dbg_msg, instance->tickTimeWork);
		LOG_DBG_TEXT(dbg_msg);
    }
}
//#ifdef __cplusplus
//}
//#endif
