/*
 * Implementation file for parse_args library.
 *
 * This class include two functions that take in command line 
 * arguments and parse them. The first simply tokenizes the 
 * arguments and tracks whether the command should be ran 
 * in the background or not. The second dynamically allocates
 * memory to each individual element of the char array.  
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse_args.h"

/*
 * A copy of the command line to which you can make your argv array point.
 * 
 * Note: Use this ONLY in the parseArguments function; DO NOT use in the
 * parseArgumentsDynamic function.
 */
static char cmdline_copy[MAXLINE];
// Globals are evil

/*
 * This function takes in a char array of user input 
 * as well as a char array to store the parsed 
 * characters. 
 *
 * @param *cmdline - Pointer to char array of user 
 * input.
 * @param **argv - Double pointer to char array
 * @result ret - 0 Run in the foreground/ 1 Run in 
 * the background.
 */
int parseArguments(const char *cmdline, char **argv) {
	unsigned int j;
	for(j = 0; j < sizeof(argv) - 1; j++) {
		argv[j] = NULL;
	}
	// Create copy of user command line arguments
	strcpy(cmdline_copy, cmdline);	 
	
	int ret = 0;
	char *token;
	char *remainder = cmdline_copy;
	char delim[] = " \n";
	unsigned int i = 0;
	
	// Loop while there are still tokens to be mined
	while((token = strtok_r(remainder, delim, &remainder))) {
		// Enable background/foreground functionality
		if(strcmp(token, "&") == 0) {
			ret = 1;
			return ret;
		}
			argv[i] = token; // Stores the parsed string
			i++;
	}
	return ret;
}

/*
 * Takes in a char array and allocated memory based on the
 * needs for each individual element. 
 *
 * @param *cmdline - Char array of user input
 * @param *bg - To enable the 
 * @result argv - A double pointer to a dynamically allocated 
 * char array of commandline arguments
 */
char **parseArgumentsDynamic(const char *cmdline, int *bg) {
	char *cmdline_cp = strdup(cmdline);
	char *cmdline_args = strdup(cmdline);
	*bg = 0;
	unsigned int i = 0;
	char *token;
	char delim[] = " \n";
	char *remainder = cmdline_cp;	
	// Loop while strtok_r remainder still has characters
	while((token = strtok_r(remainder, delim, &remainder))) {
		// Enable background/foreground functionality
		if(strcmp(token, "&") == 0) {
			*bg = 1;
			break;
		}
		i++;
	}
	i += 1; // Allocate space for NULL
	
	char **argv = calloc(i, sizeof(char **));
	unsigned int z = 0;
	char *token2; // Temp vehicle for parsed string 
	char *remainder2 = cmdline_args;
	// While remainder2 still has tokens to be discovered
	while((token2 = strtok_r(remainder2, delim, &remainder2))) {
		// Enable the background/foreground functionality
		if(strcmp(token2, "&") == 0) {
			*bg = 1;
			z++;
			break;
		}	
		int size = strlen(token2);
		argv[z] = strndup(token2, size); // Dynamically allocate space using strdup
		z++;
	}

	free(cmdline_cp); // Free memory from the heap as a result of strdup
	free(cmdline_args);
	
	return argv;
}
	
