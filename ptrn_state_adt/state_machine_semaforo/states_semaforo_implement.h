

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

#endif /* STAES_SEM_IMPLEMENT_H_ */

