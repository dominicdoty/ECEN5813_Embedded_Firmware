/*
 * validate_pattern.c
 * @brief validates a pseudorandom pattern in a memory range
 * @author D.Doty
*/

/* Includes */
#include "validate_pattern.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t validate_pattern(char* args)
{
	// Parse arguments
	uint64_t address = 0;
	uint64_t word_qty = 1;	// Default. Validates the given address only if no length is given.
	uint64_t seed = 1;		// Default. Uses 1 as seed if not provided (same as generate function).
	io_parse(args, 3, &address, &word_qty, &seed);

	// Check if the provided memory address and word quantity are in allocated block
	// Get user confirmation to proceed if they're out of range
	if(valid_range(address, word_qty) != 0)
	{
		// User has indicated they don't want to proceed. Returns to main for a new command
		return 1;
	}

	// Invert
	printf("Discrepancies will be printed below:\n");
	printf("Word#\tAddress\t\t\tContents S/B\tContents IS\n");
	clock_t begin = clock();
	uint32_t last = xorshift((uint32_t)seed);

	// Loop through the address range specified and compare against PRNG
	for(uint64_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		// If memory does not match PRNG, print that location
		if(*((uint32_t*)(address + i)) != last)
		{
			printf("%lu\t0x%016lX\t0x%08X\t0x%08X\n",
											i/sizeof(uint32_t),
											address + i,
											last,
											*((uint32_t*)(address + i)));
		}
		// Generate a new PRN for next loop
		last = xorshift(last);
	}
	
	clock_t end = clock();
	// Calculate execution time in uS to avoid floating point
	uint64_t execution_time = (1000000*(uint64_t)(end - begin))/CLOCKS_PER_SEC;
	printf("\nExecution time: %lu uS\n\n",execution_time);
	return 0;
}