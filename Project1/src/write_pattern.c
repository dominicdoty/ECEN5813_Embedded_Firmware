/*
 * write_pattern.c
 * @brief writes a pseudorandom pattern to a memory range
 * @author D.Doty
*/

/* Includes */
#include "write_pattern.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t write_pattern(char* args)
{
	// Ignore if no memory allocated
	if(block_ptr == NULL)
	{
		printf("No memory allocated to invert, use 'allocate' first\n\n");
		return -1;
	}

	// Parse arguments
	uint64_t address = 0;
	uint64_t word_qty = 1;
	uint64_t seed = 1;
	io_parse(args, 3, &address, &word_qty, &seed);

	// Check if inside allocated range
	if((address < (uint64_t)block_ptr) || ((address + word_qty*sizeof(uint32_t)) > ((uint64_t)block_ptr + block_size*sizeof(uint32_t))))
	{
		printf("This will result in a print out of the allocated range, try again\n");
		return -1;
	}

	// Invert
	printf("Writing...\n");
	clock_t begin = clock();
	uint32_t last = xorshift((uint32_t)seed);
	for(uint64_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		*((uint32_t*)(address + i)) = last;
		last = xorshift(last);
	}
	clock_t end = clock();
	uint64_t execution_time = (1000000*(uint64_t)(end - begin))/CLOCKS_PER_SEC;
	printf("Execution time: %lu uS\n\n",execution_time);
	return 1;
}