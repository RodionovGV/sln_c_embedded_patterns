#include <stdlib.h>
#include <stdio.h> // printf

#include "Module_01.h"

struct Module_private {
    const char* name;
    Data_module data;
    size_t noOfOrders;
};

// Статичный модуль
//Module_private modulo_static;

ModulePtr createModule(const char* name, const Data_module* data) {
    ModulePtr modulo = malloc(sizeof * modulo);
    //ModulePtr modulo = &modulo_static;

    if (modulo)
    {
		modulo->name = name;
        modulo->data = *data;
		modulo->noOfOrders = 0;
        modulo->data.logMessage("Hello from modulo", 0);
        modulo->data.setFlag(10);
        modulo->data.time_work++;
    }
    return modulo;
}

void showModuleData(ModulePtr p) {
    if (p == NULL) return;

    printf("%s\n", p->name);
    printf("%d", p->data.time_work);
    p->data.logMessage("showModuleData", 1);

}

void destroyModule(ModulePtr customer){
    free(customer);
}