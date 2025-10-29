

#ifndef LOGCALCMODULE_H
#define LOGCALCMODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#ifdef USE_LOG
    //------------------------------------------------------------------------------
    void log_init(const char * filename);
    void log_info(const char * msg);
    void log_destroy();
     //------------------------------------------------------------------------------

#define LOG_INIT(filename) log_init(filename)
#define LOG_DBG(text) log_info(text)
#define LOG_DESTROY() log_destroy() 

#else

#define LOG_INIT(filename) log_init(filename)
#define LOG_DBG(text) log_info(text)

#endif


#ifdef __cplusplus
}
#endif

#endif /* LOGCALCMODULE_H */

