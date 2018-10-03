/*
 * dealloc.c
 * @brief frees allocated memory
 * @author D.Doty
*/

/* Includes */
#include "dealloc.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
int8_t dealloc(char* ignore)
{
	// Check if we have a block allocated
	if(block_ptr != NULL)
	{
		// Block allocated, free it and set ptr to NULL
		free(block_ptr);
		block_ptr = NULL;
		block_size = 0;
		printf("Block freed\n\n");
		return 0;
	}
	else
	{
		// No block allocated
		printf("No memory allocated to free, use 'allocate' first\n\n");
		return 1;
	}
}