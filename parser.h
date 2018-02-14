#ifdef __PARSE_ARGS_H__
#define __PARSE_ARGS_H__

#define MAXLINE 1024
#define MAXARGS 128

int parseArguments(const char *cmdline, char *argv[]);

char **parseArgumentsDynamic(const char *cmdline, int *bg);

#endif
