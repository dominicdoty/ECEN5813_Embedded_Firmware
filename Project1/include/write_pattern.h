/*
 * write_pattern.h
 * @brief writes a pseudorandom pattern to a memory range
 * @author D.Doty
*/

/* Header Guard */
#ifndef WRITE_PATTERN_H
#define WRITE_PATTERN_H

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
int8_t write_pattern(char* args);

#endif //WRITE_PATTERN_H
