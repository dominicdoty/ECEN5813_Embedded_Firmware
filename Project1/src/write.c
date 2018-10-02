/*
 * write.c
 * @brief function to write a memory location
 * @author D.Doty
*/

/* Includes */
#include "write.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t write(char* args)
{
	// Ignore if no memory allocated
	if(block_ptr == NULL)
	{
		printf("No memory allocated to write, use 'allocate' first\n\n");
		return -1;
	}

	// Parse arguments
	uint64_t address = 0;
	uint64_t word = 0;
	io_parse(args, 2, &address, &word);

	// Check if inside allocated range
	if((address < (uint64_t)block_ptr) || (address >= ((uint64_t)block_ptr + block_size*sizeof(uint32_t))))
	{
		printf("This will result in a write out of the allocated range, try again\n");
		return -1;
	}

	// Write
	printf("Writing...\n");
	printf("Address\t\t\tContents Hex\tContents Dec\n");
	*((uint32_t*)address) = word;
	printf("0x%016lX\t0x%08X\t%d\n\n", address, *((uint32_t*)address), *((uint32_t*)address));
	return 1;
}