/*
 * help.c
 * @brief display basic user help messages
 * @author D.Doty
*/

/* Includes */

#include "help.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */

void help_welcome()
{
	printf("Welcome to Memory Tester\n");
	printf("For command list type 'help'\n");
}

int8_t help()
{
	printf("Commands:\n");
	for (int i = 0; i < command_quantity; i++)
	{
		printf("%s - %s\n", command_human[i], command_help[i]);
	}
	return 1;
}
