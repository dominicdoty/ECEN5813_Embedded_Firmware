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
#include "commandtable.h"
#include "io.h"
#include "help.h"
#include "end.h"
#include "allocate.h"
#include "dealloc.h"


/* Defines */



/* Function Prototypes */



/* Global Variables */
uint32_t* block_ptr = NULL;
uint32_t block_size = 0;

/* Main */
int main()
{
	command_table_init(4);
	add_command("help", "returns list of available commands and their function, no arguments", help);
	add_command("exit", "exits the program, all is lost, no arguments", end);
	add_command("allocate", "allocates a block of memory, argument is number of 32 bit words to allocate\n\t in decimal or hex (0x prepend)", allocate);
	add_command("free", "frees the currently allocated block of memory, no arguments", dealloc);

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
