/* 
 * File:   Module_private.h
 * Author: RodionovGV
 *
 * Created on October 17, 2025
 */

#ifndef MODULE_01_H
#define MODULE_01_H

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct {
        char name[32];              // Имя модуля
        unsigned int time_work;     // Время работы модуля в секундах
        int data_reserv_ctrl[32];

        int(*setFlag)(int flag);                               // Какой-то флаг
        void (*logMessage)(const char* msg, int severity);     // Функция логирования

        int data_resev_data[128];
    }Data_module;
    
    // ADT, не завершённый тип
    typedef struct Module_private* ModulePtr;

    // Прототипы функций
    ModulePtr createModule(const char* name, const Data_module* data);
    void showModuleData(ModulePtr p);
    void destroyModule(ModulePtr customer);

#ifdef __cplusplus
}
#endif

#endif /* MODULE_01_H */

