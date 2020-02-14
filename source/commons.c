#include "../headers/commons.h"

void _abort(const char *s)
{
  perror(s);
  abort();
}
