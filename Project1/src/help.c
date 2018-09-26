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
	printf("Welcome to Memory Tester\r\n");
	printf("For command list type 'help'\r\n");
}

int8_t help(uint32_t disregard, uint32_t disregard2)
{
	printf("Commands:\r\n");
	for (int i = 0; i < command_quantity; i++)
	{
		printf("%s - %s\r\n", command_human[i], command_help[i]);
	}
	return 1;
}
