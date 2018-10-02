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
	// Ignore if no memory allocated
	if(block_ptr == NULL)
	{
		printf("No memory allocated to display, use 'allocate' first\n\n");
		return -1;
	}

	// Parse arguments
	uint64_t address = 0;
	uint64_t word_qty = 1;
	io_parse(args, 2, &address, &word_qty);

	// Check if inside allocated range
	if((address < (uint64_t)block_ptr) || ((address + word_qty) > ((uint64_t)block_ptr + block_size)))
	{
		printf("This will result in a print out of the allocated range, try again\n");
		return -1;
	}

	// Display
	printf("Word#\tAddress\t\t\tContents Hex\tContents Decimal\n");
	for(uint8_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		printf("%ld\t0x%016lX\t0x%08X\t%d\n",i/sizeof(uint32_t),
											address + i,
											*((uint32_t*)(address + i)),
											*((uint32_t*)(address + i)));
	}
	printf("\n");
	return 1;
}
