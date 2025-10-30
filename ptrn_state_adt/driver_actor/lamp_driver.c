#include <stdio.h>
#include <stdlib.h>

#include "logModule.h"
#include "lamp_driver.h"

typedef struct LampDriver* LampDriverPtr;

// ��������� ��� �������
typedef void (*LampActionFunc)(void);

struct LampDriver {
    // ������ ��������
    int gpio_pin;
    int counter;
};

// �������� ������ �������
LampDriverPtr driver = NULL;

void createLampDriver(void) {
    driver = malloc(sizeof * driver);
    if (driver) {
        driver->gpio_pin = 123; // ������
        driver->counter = -10;
    }
    return;
}

void destroyLampDriver() {
    free(driver);
}

void turnOnLamp() {
    driver->gpio_pin = 1;
	LOG_DBG_TEXT("turnOnLamp()");
    //printf("Lamp ON (GPIO %d)\n", driver->gpio_pin);
    // �������� ������ ��������� �����
}

int turnWaitLamp(void) {
    int result = 0;
    driver->counter++;
    if (driver->counter > 10) {
        result = 1;
    }
    return result;
}

void turnOffLamp() {
    driver->gpio_pin = 0;
	LOG_DBG_TEXT("turnOffLamp()");
    //printf("Lamp OFF (GPIO %d)\n", driver->gpio_pin);
    // �������� ������ ���������� �����
}