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
#include "invert.h"
#include "write_pattern.h"
#include "validate_pattern.h"


/* Defines */



/* Function Prototypes */



/* Global Variables */
uint32_t* block_ptr = NULL;
uint32_t block_size = 0;

/* Main */
int main()
{
	// Initialize the command table and fill it
	command_table_init(9);
	add_command("help", "returns list of available commands and their function, no arguments", help);
	add_command("exit", "exits the program, all is lost, no arguments", end);
	add_command("allocate", "allocates a block of memory,\n\t\targument is number of 32 bit words to allocate", allocate);
	add_command("free", "frees the currently allocated block of memory, no arguments", dealloc);
	add_command("display", "displays memory contents at a specified address range,\n\t\targument is start_address and length of block to display", display);
	add_command("write", "writes provided 32 bit word to specified address,\n\t\targument is memory_address and 32bit word", write);
	add_command("invert", "inverts contents at a specified address range,\n\t\targument is the memory_address and length of block to invert", invert);
	add_command("prng", "writes pseudo random 32 bit words to specified address range,\n\t\targument is the memory_address, length of block to write, and prng seed", write_pattern);
	add_command("validate", "validates pseudo random 32 bit words at specified address range,\n\t\targument is the memory_address, length of block to validate, and prng seed\n\t\tnote this won't work with a different starting address or seed. default seed is 1", validate_pattern);

	// Print the welcome message
	help_welcome();

	// Loop forever getting user commands
	while(1)
	{
		printf(">>");					// Input point marker
		struct io result = {-1, ""};	// Init the user input structure
		result = cmd_get();				// Get the user input
		if(result.command != -1)		// If command is valid, execute it
		{
			command_table[result.command](result.args);
		}
	}
}
