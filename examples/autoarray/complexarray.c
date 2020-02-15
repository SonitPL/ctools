/*
  Przykład programu wykorzystującego złożony typ danych.
*/

#include "../../headers/autoarray.h"

//struktura złożonego typu danych
typedef struct
{
  char* data;
  size_t length;
  size_t max_length;
} string;

//konstruktor pustego
string create(size_t max_length)
{
  string result;
  result.data = malloc(max_length);
  if(result.data == NULL) abort();

  memset(result.data, 0, max_length); 
  result.length = 0;
  result.max_length = max_length;
  return result;
}

string create_full(const char* s, size_t max_length)
{
  string result = create(max_length);
  int length = strlen(s);
  memcpy(result.data, s, length);
  result.length = length;
  return result;
}

//destruktor
void destroy(void* p)
{
  string* s = (string*)p;
  free(s->data);
  s->length = 0;
  s->max_length = 0;
  s->data = NULL;
}

//funkcja kopiująca: z source do dest
void* copy(void* _dest, const void* _source, size_t element_size)
{
  string* dest = (string*)_dest;
  string* source = (string*)_source;
  string result = create_full("\0",source->max_length);
  memcpy(result.data, source->data, source->length);
  result.length = source->length;
  result.max_length = source->max_length;
  *dest = result;
  return dest;
}

int main(void)
{
  aarray tab = acreate_complex(string, destroy, copy);
  //prezentacja, że zmiana danych w s.data nie powoduje zmiany
  //pola data elementów na tablicy
  string s = create_full("aaaaaaa\0", 8); apush(tab, string, s);
  memcpy(s.data, "bbbbbbb\0", 8); apush(tab, string, s);
  memcpy(s.data, "ccccccc\0", 8); apush(tab, string, s);
  for(string* i = abegin(tab, string); i != aend(tab, string); ++i)
  {
    printf("%s\n", (*i).data);
  }
  adestroy(&tab);
  destroy(&s);
}



