#ifndef STATES_SEM_DEFAULT_H_ 
#define STATES_SEM_DEFAULT_H_

//#ifdef __cplusplus
//extern "C" {
//#endif

typedef struct StateSemaforo* StateSemaforoPtr;


// Структура событий состояния
typedef struct StateSemEvents {
	void (*on_entry)(void);
	void (*on_do)(void);
	void (*on_exit)(void);
	long (*check_change_state)(void);
	long workTimeToSwitch;
} StateSemEvents;

void defaultSemaforoImplementation(StateSemaforoPtr s);

//#ifdef __cplusplus
//}
//#endif

#endif /* STATES_SEM_DEFAULT_H_ */

