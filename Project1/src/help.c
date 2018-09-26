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
	printf("\nWelcome to Memory Tester\n");
	printf("For command list type 'help'\n\n");
}

int8_t help(uint32_t disregard, uint32_t disregard2)
{
	printf("Commands:\n");
	for (int i = 0; i < command_quantity; i++)
	{
		printf("%s - %s\n", command_human[i], command_help[i]);
	}
	printf("\n");
	return 1;
}
