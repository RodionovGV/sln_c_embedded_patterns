/*
Модуль логгирования, для возможного использования различных логгеров.

*/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef USE_LOG

#include <slog.h>

// 
slog_config_t cfg;
int nInteger = 69;
char sBuffer[14];

static void log_greet()
{
	/* Get and print slog version */
	slog("=========================================");
	slog("Debug session START SLog Version: %s", slog_version(0));
	slog("=========================================");
}

static void log_bye()
{
	/* Get and print slog version */
	slog("=========================================");
	slog("Debug session END SLog Version: %s", slog_version(0));
	slog("=========================================");
}

void log_init(const char * filename){
    
	/* Initialize slog and allow only error and not tagged output */
	slog_init(filename, SLOG_FLAGS_ALL, 0);
	slog_config_get(&cfg);
	cfg.nToFile = 1;
	slog_config_set(&cfg);
	log_greet();
}

void log_info(const char * msg){
        /* Info message with char*/
    slog(msg);
}

void log_destroy(){
	log_bye();
	slog_destroy();
}


#else

#endif

#ifdef __cplusplus
}
#endif
