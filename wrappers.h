#ifndef __WRAPPERS_H__
#define __WRAPPERS_H__

pid_t Fork(void);
void unix_error(char *msg);
void child_handler(__attribute__ ((unused)) int sig);
int isNumber(char *number); 

#endif
