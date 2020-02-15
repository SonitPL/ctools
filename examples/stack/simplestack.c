/*
  Przykład użycia stosu na prostym typie danych.
*/
#include "../../headers/stack.h"


int main(void)
{
  stack s = screate(int);
  spush(s, int, 37);
  spush(s, int, 21);
  printf("Na szczycie stosu jest: %d\n", stop(s, int));
  spop(s);
  printf("Teraz na szczycie stosu jest: %d\n", stop(s, int));
  for( int i = 0; i < 10; ++i) spush(s, int, i);
  printf("Aktualna liczba elementow na stosie: %ld\n", ssize(s));
  printf("Pojedynczy element zajmuje: %ld bajtow\n",selement_size(s));
  serase(s);    //kasujemy wszystko ze stosu
  printf("Czy teraz stos jest pusty? 1 tak, 0 nie: %d\n",sempty(s));
  sdestroy(&s);
}
