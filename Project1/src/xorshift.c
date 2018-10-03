/*
 * xorshift.c
 * @brief uses the xorshift PRNG by George Marsaglia
 * https://en.wikipedia.org/wiki/Xorshift
 * @author D.Doty
*/

/* Includes */
#include "xorshift.h"

/* Defines */


/* Global Variables */


/* Private Function Prototypes */


/* Function Definition */
// Note that this implementation is extremely similar to the one covered in
// "Xorshift RNGs" by George Marsaglia
// I do not claim this as my original work
uint32_t xorshift(uint32_t last_value)
{
	last_value ^= last_value << 13;
	last_value ^= last_value >> 17;
	last_value ^= last_value << 5;
	return last_value;
}