/*
 * xorshift.h
 * @brief uses the xorshift PRNG by George Marsaglia
 * https://en.wikipedia.org/wiki/Xorshift
 * @author D.Doty
*/

/* Header Guard */
#ifndef XORSHIFT_H
#define XORSHIFT_H

/* Includes */
#include <stdint.h>

/* Defines */


/* Global Variables */


/* Global Function Prototypes */
uint32_t xorshift(uint32_t last_value);

#endif //XORSHIFT_H
