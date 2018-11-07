#ifndef ERROR_MORSE_
#define ERROR_MORSE_

#include <stdio.h>
#include <stdbool.h>

typedef struct{
  uint8_t high,low
} num

num add_check(uint8_t c);

bool check_is_ok(uint8_t mensaje[]);

num add_crc(uint8_t mensaje[]);

bool crc_is_ok(uint8_t mensaje[]);


#endif
