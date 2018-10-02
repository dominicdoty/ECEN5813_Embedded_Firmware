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
#include "display.h"
#include "write.h"


/* Defines */



/* Function Prototypes */



/* Global Variables */
uint32_t* block_ptr = NULL;
uint32_t block_size = 0;

/* Main */
int main()
{
	command_table_init(6);
	add_command("help", "returns list of available commands and their function, no arguments", help);
	add_command("exit", "exits the program, all is lost, no arguments", end);
	add_command("allocate", "allocates a block of memory,\n\t\targument is number of 32 bit words to allocate", allocate);
	add_command("free", "frees the currently allocated block of memory, no arguments", dealloc);
	add_command("display", "displays memory contents at a specific address,\n\t\targument is start_address and length of block", display);
	add_command("write", "writes provided 32 bit word to specified address,\n\t\targument is memory_address and 32bit word", write);

	help_welcome();

	while(1)
	{
		printf(">>");
		struct io result = cmd_get();
		if(result.command != -1)
		{
			command_table[result.command](result.args);
		}
	}
}
