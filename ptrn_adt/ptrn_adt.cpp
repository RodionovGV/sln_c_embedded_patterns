// ptrn_adt.cpp : запуск примера adt шаблона 
//

#include <iostream>

#include "logModule.h"

#include "Module_01.h"

int fxn(int flag) {
    std::cout << "fxn flag: " << flag << "\n";
    return flag;
}

void log(const char* msg, int severity) {
    if (severity) {
		printf("%s", msg);
    }
}

int main()
{
    std::cout << "Hello World!\n";

    Data_module d_module = {.time_work = 0, .setFlag = fxn, .logMessage = log };

    ModulePtr p_module = createModule("Modulo2026", &d_module);

    showModuleData(p_module);
    destroyModule(p_module);
}

