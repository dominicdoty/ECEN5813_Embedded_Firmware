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
	uint64_t word_qty = 1;
	uint64_t seed = 1;
	io_parse(args, 3, &address, &word_qty, &seed);

	// Check for valid inputs
	if(valid_range(address, word_qty) != 0)
	{
		return 1;
	}

	// Invert
	printf("Discrepancies will be printed below:\n");
	printf("Word#\tAddress\t\t\tContents S/B\tContents IS\n");
	clock_t begin = clock();
	uint32_t last = xorshift((uint32_t)seed);
	for(uint64_t i = 0; i < word_qty*sizeof(uint32_t); i += sizeof(uint32_t))
	{
		if(*((uint32_t*)(address + i)) != last)
		{
			printf("%lu\t0x%016lX\t0x%08X\t0x%08X\n",
											i/sizeof(uint32_t),
											address + i,
											last,
											*((uint32_t*)(address + i)));
		}
		last = xorshift(last);
	}
	clock_t end = clock();
	uint64_t execution_time = (1000000*(uint64_t)(end - begin))/CLOCKS_PER_SEC;
	printf("\nExecution time: %lu uS\n\n",execution_time);
	return 0;
}