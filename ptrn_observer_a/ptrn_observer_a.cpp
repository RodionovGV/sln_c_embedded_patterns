// ptrn_observer_a.cpp : 
//

#include <iostream>

extern "C" {
    #include "DigitalStopWatch.h"
    #include "TimeSubject.h"
    void stepTime();
}

int main()
{
    std::cout << "Hello World!\n";
    DigitalStopWatchPtr w = createDigitalWatch();
    if (w == NULL) {
        exit(1);
    }

    stepTime();
    return 0;
}

