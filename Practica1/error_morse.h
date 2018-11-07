#ifndef ERROR_MORSE_
#define ERROR_MORSE_

#include <stdio.h>
#include <stdbool.h>

typedef struct{
  uint8_t a,b
} num

num add_check(char c);

char get_redun(char c);

bool check_is_ok(char c);

#endif
