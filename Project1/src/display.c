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

	// Check for valid inputs
	if(valid_range(address, word_qty) != 0)
	{
		return 1;
	}

	// Display
	printf("Word#\tAddress\t\t\tContents Hex\tContents Decimal\n");
	for(uint8_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		printf("%lu\t0x%016lX\t0x%08X\t%u\n",i/sizeof(uint32_t),
											address + i,
											*((uint32_t*)(address + i)),
											*((uint32_t*)(address + i)));
	}
	printf("\n");
	return 0;
}
