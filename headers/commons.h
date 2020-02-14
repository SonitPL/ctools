/*
  Używane przez implementacje biblioteki i funkcje.
*/
#ifndef COMMONS_H
#define COMMONS_H
//malloc, realloc
#include <stdlib.h>
//printf, fprintf, strerr
#include <stdio.h>
//memcpy, memmove
#include <string.h>
//errno
#include <errno.h>


//przerywa program z komunikatem błędu danym jako argument
void _abort(const char*s);

#endif
