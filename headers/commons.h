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


//przerywa program z nazwą funkcji daną jako argument
//treść komunikatu błędu dana jest przez zmienną [errno]
void _abort(const char *funcname);

//przerywa program z nazwą funkcji i komunikatem błędu
//do błędów, które nie są zgłoszone przez funkcje libc
void report_error(const char *funcname, const char *errortext);

#endif
