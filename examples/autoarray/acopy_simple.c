/*
  Przykład użycia funkcji kopiującej tablicę na prostym typie danych.
*/
#include "../../headers/autoarray.h"

int main(void)
{
  aarray tab = acreate(int);
  apush(tab, int, 6);
  apush(tab, int, 9);
  aarray t;
  acopy(&t, &tab, sizeof(int));
  abegin(t, int)[0] = 4;
  abegin(t, int)[1] = 2;
  printf("%d%d:%d%d", abegin(tab,int)[0],abegin(tab,int)[1],
    abegin(t,int)[0],abegin(t,int)[1]);
  
  adestroy(&tab);
  adestroy(&t);

}

