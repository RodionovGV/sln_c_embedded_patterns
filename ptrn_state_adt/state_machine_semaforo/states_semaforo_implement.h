

#ifndef STAES_SEM_IMPLEMENT_H_ 
#define STAES_SEM_IMPLEMENT_H_

//#ifdef __cplusplus
//extern "C" {
//#endif

typedef struct SemaforoMaker* SemaforoMakerPtr;

void destroySemaforo(SemaforoMakerPtr instance);
SemaforoMakerPtr createSemaforo(void);

void semaforo_stae_mashine(SemaforoMakerPtr instance);

//#ifdef __cplusplus
//}
//#endif

// i prototipi per testi
SemaforoMakerPtr createSemaforo(void);
void destroySemaforo(SemaforoMakerPtr instance);
long getWorkTicks();

void stateYellow(SemaforoMakerPtr instance);
void stateRed(SemaforoMakerPtr instance);
void stateRedYellow(SemaforoMakerPtr instance);
void stateGreen(SemaforoMakerPtr instance);
void stateGreenBlink(SemaforoMakerPtr instance);
void stateYellowBlink(SemaforoMakerPtr instance);
void semaforo_stae_mashine(SemaforoMakerPtr instance);

#endif /* STAES_SEM_IMPLEMENT_H_ */

