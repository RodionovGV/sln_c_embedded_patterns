#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "SystemTime.h"
#include "TimeSubject.h"
#include "DigitalStopWatch.h"

/*
I never really dive into the details of this type.
Let's just create a dummy placeholder for the information.
*/
typedef struct 
{
  int someDisplayAttributes;
  long int selfTime;
} Display;

struct DigitalStopWatch 
{
  Display watchDisplay;
  /* Other attributes of the watch. */
};

/* Dummy stub for the responsibility of updating the 
   display on the watch. */
static void updateDisplay(DigitalStopWatchPtr watch,
                          const SystemTime* newTime)
{
  Display* display = &watch->watchDisplay;
  watch->watchDisplay.selfTime = newTime->theTime; // обновляем время для часов
  /* Do the update...*/
}

/* Implementation of the function required by the
   TimeObserver interface. */
static void changedTime(void* instance, const SystemTime* newTime) 
{
  DigitalStopWatchPtr digitalWatch = instance;
  assert(NULL != digitalWatch);
  updateDisplay(digitalWatch, newTime);
}

DigitalStopWatchPtr createDigitalWatch(void) 
{
  DigitalStopWatchPtr watch = malloc(sizeof *watch);
  printf("DigitalStopWatchPtr 0x%X\n", watch);
  if(NULL != watch) {
      watch->watchDisplay.selfTime = 0;
    /* Successfully created -> attach to the subject. */
    TimeObserver observer = {0};
    observer.instance = watch;
    observer.notification = changedTime;
    attach(&observer);
  }

  return watch; 
}

long int currentTime(DigitalStopWatchPtr w) {
    return w->watchDisplay.selfTime;
}

void destroyDigitalWatch(DigitalStopWatchPtr watch)
{
  /* Before deleting the instance we have to detach
     from the subject. */
  TimeObserver observer = {0};
  observer.instance = watch;
  observer.notification = changedTime;
  detach(&observer);
  free(watch);
}


