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
int8_t dealloc(uint32_t unused, uint32_t ignore)
{
	free(block_ptr);
	block_ptr = NULL;
	block_size = 0;
	printf("Block Freed\n\n");
	return 1;
}