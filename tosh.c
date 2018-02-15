/*
 * The Not-So-Tiny Torero Shell (TOSH)
 *
 * Add your top-level comments here.
 */

/*
 * TODO list:
 *		(1) Convert execvp to execv
 *			(1a) build argv list for execv -- look at project info
 *		(2) built in commands - cd, exit, history, !num, !! 
 *			(All done except '!!' command)
 *		(3) io redirection
 *		(4) pipes
 *		(5) constant testing
 */

#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <ctype.h>
#include <libgen.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <sys/errno.h>
#include <readline/readline.h>

#include "wrappers.h"
#include "parse_args.h"
#include "history_queue.h"

// TODO: add your function prototypes here as necessary

void cd(char *argv[]);
void nextDir(char *argv[]);
int isBuiltIn(char *argv[]);
int isBangNum(char cmd[MAXLINE]);
int shellEntry(char cmdline[MAXLINE]);
void execCmd(char *argv[], int ret);

static void printBG(int bg);
static void printCommandArgs(char *cmdline, char **argv);

int main(){ 

    // TODO: add a call to signal to register your signal handler on 
    //       SIGCHLD here

    struct sigaction sa;
    sa.sa_handler = child_handler;
    sa.sa_flags = SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    while(1) {
        // (1) read in the next command entered by the user
        /** char cmdline[MAXLINE];	 */


        char *cmdline = readline("tosh$ ");

        // fgets instead of readline, attempt to fix the makefile error
        //
        // this was not causing the error but leaving it for choice later
        // between fgets and readline
        /** if((fgets(cmdline,MAXLINE, stdin) == NULL) && ferror(stdin)) { */
        /**     clearerr(stdin); */
        /**     continue; */
        /** } */
        /** if(feof(stdin)) { */
        /**     fflush(stdout); */
        /**     exit(0); */
        /** } */
        /** if(shellEntry(cmdline) == 1) { */
        /**     continue; */
        /** } */
        /**  */
        // NULL indicates EOF was reached, which in this case means someone
        // probably typed in CTRL-d
        if (cmdline == NULL) {
            fflush(stdout);
            exit(0);
        }

        fprintf(stdout, "DEBUG: %s\n", cmdline);

        // TODO: complete the following top-level steps
        // (2) parse the cmdline
        //char **args = NULL;
        
		char cmd[sizeof(cmdline)];
		strcpy(cmd, cmdline);
		//cmd = strdup(cmdline);
		if(shellEntry(cmd) == 1) {
			continue;
		}
		
		/*
		char *argv[MAXARGS];
        int bg = 0;

        //unsigned int i = 0;
        bg = parseArguments(cmdline, argv);

        printCommandArgs(cmdline, argv);
        printBG(bg);
        
		*/


		/*
        //args = parseArgumentsDynamic(cmdline, &bg);
        if (args) {
        printCommandArgs(cmdline, args);
        printBG(bg);
        while(args[i] != NULL) {
        free(args[i]);
        i++;
        }
        free(args);
        }
        */
        // TODO:(3) determine how to execute it, and then execute it
		free(cmdline);
    }
    return 0;
}

/**
 *
 */
int shellEntry(char cmdline[MAXLINE]) { 
    char *argv[MAXARGS];
	int add = isBangNum(cmdline);
	if(add == 0) {
		fprintf(stdout, "ERROR: command not in history");
		return 0;
	}
	
	int ret = parseArguments(cmdline, argv);
	printCommandArgs(cmdline, argv);
	printBG(ret);
	if(argv[0] == NULL) {
		return 1;
	}
	if(add == 1) {
		addEntry(cmdline); // Function from history_queue
	}
	if(isBuiltIn(argv) == 1) {
		return 1;
	}
    execCmd(argv, ret);
	return 0; 
}

/**
 *
 */
int isBangNum(char cmd[MAXLINE]) { 
    int ret = 1;
    if (cmd[0] == '!') {
        memmove(cmd,cmd+1,strlen(cmd));
        ret = numToCmd(cmd);
    }
    return ret; 
}

/**
 * Execute commands in argv
 * @param argv Command line arguments
 * @param ret Determines if command to run in the foreground
 * or background
 */
void execCmd(char *argv[], int ret) {
    int status;
    pid_t child_pid;
    if((child_pid = Fork()) == 0) {
        setpgid(0,0);
        if(execvp(argv[0], argv) == -1) {
            fprintf(stdout, "ERROR: command not found\n");
            exit(0);
        }
    }
    else if (ret == 0) { // Foreground
        waitpid(child_pid, &status, 0); // Wait for child
    }
}

/**
 *
 */
int isBuiltIn(char *argv[]){  
    if (strcmp(argv[0], "exit") == 0) {
        fprintf(stdout, "Adios mi amigo...\n");
        exit(0);
    }
    else if (strcmp(argv[0], "history") == 0) {
        printHistory();
        return 1;
    }
    else if (strcmp(argv[0], "cd") == 0) {
        cd(argv);
        return 1;
    }
    return 0; 
}

/**
 *
 */
void cd(char *argv[]) {
    if(argv[1] == NULL) {
        chdir(getenv("HOME"));
        return;
    } 
    else if (chdir(argv[1]) == -1) { 
        fprintf(stdout, "directory does not exist\n");
    }
    return;
}

/**
 *
 */
void nextDir(char *argv[]) { 
    char cwd[MAXLINE];
    char *new_cwd = NULL;
    getcwd(cwd, sizeof(cwd));

    new_cwd = strcat(cwd, "/");
    new_cwd = strcat(new_cwd, argv[1]);
	if(chdir(new_cwd) == -1) {
		fprintf(stdout, "directory does not exist\n");
	}
    return;
}

/**
 * This function prints the the background status of the 
 * command
 *
 */
void printBG(int bg) {
    if(bg) {
        printf("run in the background is true\n");
    } else {
        printf("rund in the background is false\n");
    }
}

/**
 *
 */
void printCommandArgs(char *cmdline, char **argv) {
    printf("\nCommand line: %s\n", cmdline);

    unsigned i = 0;
    while(argv[i] != NULL) {
        printf("%3d	#%s#\n", i, argv[i]);
        i++;
    }
}


