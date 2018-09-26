/*
 * io.h
 * @brief Input/Output functions
 * @author D.Doty
*/

/* Header Guard */
#ifndef IO_H
#define IO_H

/* Includes */
#include <stdio.h>
#include <stdint.h>
#include <string.h>


/* Defines */
#define MAX_INPUT_LENGTH 36

/* Global Variables */
struct io
{
	uint8_t command;
	uint32_t arg1;
	uint32_t arg2;
};


/* Global Function Prototypes */
struct io io_get();


#endif //IO_H
