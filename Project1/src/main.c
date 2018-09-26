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
#include "help.h"
#include "commandtable.h"


/* Defines */



/* Function Prototypes */



/* Global Variables */



/* Main */
int main()
{
	command_table_init(1);
	add_command("help", "returns list of available commands and their function", help);

	help_welcome();

	while(1)
	{
		io_get();
		//io_parse();
		//command_table_execute();
	}
}
