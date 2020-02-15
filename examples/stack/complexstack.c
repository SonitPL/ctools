/*
  Przykład użycia stosu z złożonym typem danych.
*/
#include "../../headers/stack.h"

typedef struct
{
  char* s;
} string;

string create(const char *s)
{
  string result;
  result.s = malloc(1024);
  if(result.s == NULL) abort();
  memset(result.s, 0, 1024);
  memcpy(result.s, s, strlen(s));
  return result;
}

void destroy(void* _s)
{
  string* s = (string*)_s;
  free(s->s);
}

void* copier(void* _dest, const void* _source, size_t element_size)
{
  string* dest = (string*)_dest;
  string* source = (string*)_source;
  string result;
  result.s = malloc(1024);
  if(result.s == NULL) abort();
  memset(result.s, 0, 1024);
  memcpy(result.s, source->s, 1024);
  *dest = result;
  return _dest;
}

int main(void)
{
  stack s = screate_complex(string, destroy, copier);
  string a = create("*******");
  spush(s, string, a); destroy(&a); a = create(" *****");
  spush(s, string, a); destroy(&a); a = create("  ***");
  spush(s, string, a); destroy(&a); a = create("   *");
  spush(s, string, a); destroy(&a); 
  while(!sempty(s))
  {
    printf("%s\n", stop(s, string).s);
    spop(s);
  }
  sdestroy(&s);
}
