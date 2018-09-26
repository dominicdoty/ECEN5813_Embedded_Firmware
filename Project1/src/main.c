/*
 * D.Doty
 * ECEN 5813
 * CU Boulder
 * Fall 2018
 * Project 1
*/


/* Includes */
#include <stdio.h>
#include <stdint.h>
#include "end.h"
#include "help.h"
#include "commandtable.h"
#include "io.h"


/* Defines */



/* Function Prototypes */



/* Global Variables */



/* Main */
int main()
{
	command_table_init(2);
	add_command("help", "returns list of available commands and their function", help);
	add_command("exit", "exits the program, all is lost", end);

	help_welcome();

	while(1)
	{
		struct io result = io_get();
		if(result.command != -1)
		{
			command_table[result.command](result.arg1, result.arg2);
		}
	}
}
