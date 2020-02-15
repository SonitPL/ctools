/*
  Przykład użycia [lcopy]
*/
#include "../../headers/list.h"

void wypisz(void* arg)
{
  int* a = (int*)arg;
  printf("%d", *a);
}

int main(void)
{
  list l = lcreate(int);
  lpush_back(l, int, 21);
  lpush_back(l, int, 37);
  list li = lcopy(l);
  lvalue(lbegin(l), int) = 73;
  lvalue(lnext(lbegin(l)), int) = 12;
  liter(l, wypisz); puts("");
  liter(li, wypisz); puts("");
  ldestroy(&l);
  ldestroy(&li);
}
