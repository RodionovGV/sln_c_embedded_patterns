// ptrn_observer_a.cpp : 
//

#include <iostream>

extern "C" {
    #include "DigitalStopWatch.h"
    void stepTime();
}

int main()
{
    std::cout << "Hello World!\n";
    long int showTime = 0;
    DigitalStopWatchPtr w1 = createDigitalWatch();
    if (w1 == NULL) {
        exit(1);
    }
    showTime = currentTime(w1);

    std::cout << "w1:" << showTime << "\n";


    // Обновляем время
    // все наблюдатели должны быть оповещены
    for (int i = 0; i < 100; i++) {
		stepTime();
    }
    showTime = currentTime(w1);
    std::cout << "w1:" << showTime << "\n";

    // вторые часты
    DigitalStopWatchPtr w2 = createDigitalWatch();
    if (w2 == NULL) {
        exit(1);
    }
    showTime = currentTime(w2);
    
    std::cout << "w2:" << showTime << "\n";

    // Обновляем время
    // все наблюдатели должны быть оповещены
    for (int i = 0; i < 100; i++) {
		stepTime();
    }

    showTime = currentTime(w1);
    std::cout << "w1:" << showTime << "\n";

    showTime = currentTime(w2);
    std::cout << "w2:" << showTime << "\n";
    destroyDigitalWatch(w1);
    destroyDigitalWatch(w2);
    return 0;
}

