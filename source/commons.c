#include "../headers/commons.h"

void _abort(const char *funcname)
{
  perror(funcname);
  abort();
}

void report_error(const char *funcname, const char *errortext)
{
  fprintf(stderr,"%s: %s\n", funcname, errortext);
  abort();
}
