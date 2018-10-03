/*
 * display.c
 * @brief function to display a memory location
 * @author D.Doty
*/

/* Includes */
#include "display.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t display(char* args)
{
	// Parse arguments
	uint64_t address = 0;
	uint64_t word_qty = 1;
	io_parse(args, 2, &address, &word_qty);

	// Check if the provided memory address and word quantity are in allocated block
	// Get user confirmation to proceed if they're out of range
	if(valid_range(address, word_qty) != 0)
	{
		// User has indicated they don't want to proceed. Returns to main for a new command
		return 1;
	}

	// Display
	printf("Word#\tAddress\t\t\tContents Hex\tContents Decimal\n");

	for(uint8_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		printf("%lu\t0x%016lX\t0x%08X\t%u\n",
				i/sizeof(uint32_t),				// Block #
				address + i,					// Address
				*((uint32_t*)(address + i)),	// Address Contents Hex
				*((uint32_t*)(address + i)));	// Address Contents Decimal
	}
	printf("\n");
	return 0;
}
