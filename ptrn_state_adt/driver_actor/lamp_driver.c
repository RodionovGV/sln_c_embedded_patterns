#include "lamp_driver.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct LampDriver* LampDriverPtr;

// Объявляем тип функции
typedef void (*LampActionFunc)(void);

struct LampDriver {
    // данные драйвера
    int gpio_pin;
};

// статично создаю драйвер
LampDriverPtr driver = NULL;

void createLampDriver(void) {
    driver = malloc(sizeof * driver);
    if (driver) {
        driver->gpio_pin = 123; // пример
    }
    return;
}

void destroyLampDriver() {
    free(driver);
}

void turnOnLamp() {
    driver->gpio_pin = 1;
    printf("Lamp ON (GPIO %d)\n", driver->gpio_pin);
    // реальная логика включения света
}

void turnOffLamp() {
    driver->gpio_pin = 0;
    printf("Lamp OFF (GPIO %d)\n", driver->gpio_pin);
    // реальная логика выключения света
}