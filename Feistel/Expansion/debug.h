#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUGFLAG
	#define DBG_dot()			printf(".")
	#define DBG_fdot()			printf(".\n")
	#define DBG_info(M, ...)	fprintf(stderr, "[INFO] (%s:%d) " M, \
			__FILE__, __LINE__, ##__VA_ARGS__)
	#define DBG_infoln(M, ...)	fprintf(stderr, "[INFO] (%s:%d) " M "\n", \
			__FILE__, __LINE__, ##__VA_ARGS__)
#else
	#define DBG_dot()
	#define DBG_fdot() 
	#define DBG_info(M, ...)
	#define DBG_infoln(M, ...)
#endif

#endif
