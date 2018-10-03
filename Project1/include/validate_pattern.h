/*
 * validate_pattern.h
 * @brief validates a pseudorandom pattern in a memory range
 * @author D.Doty
*/

/* Header Guard */
#ifndef VALIDATE_PATTERN_H
#define VALIDATE_PATTERN_H

/* Includes */
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "io.h"
#include "xorshift.h"

/* Defines */


/* Global Variables */
extern uint32_t* block_ptr;
extern uint32_t block_size;

/* Global Function Prototypes */
int8_t validate_pattern(char* args);

#endif //VALIDATE_PATTERN_H
