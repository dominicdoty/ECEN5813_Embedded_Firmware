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
#include <stdarg.h>
#include "commandtable.h"


/* Defines */
#define MAX_INPUT_LENGTH 36

/* Global Variables */
struct io
{
	int8_t command;
	char args[MAX_INPUT_LENGTH];
};


/* Global Function Prototypes */
struct io cmd_get();

void io_parse(char* arg_string, uint8_t arg_qty, ...);

uint64_t string_num(char* string);

uint64_t string_dec(char* string);

uint64_t string_hex(char* string);

uint64_t power(uint32_t base, uint32_t exponent);

#endif //IO_H
