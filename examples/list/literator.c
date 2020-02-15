/*
  Przykład korzystania z literatora (oraz z [liter]).
*/

#include "../../headers/list.h"

//funkcja wypisująca do [liter]
void wypisz(void* a_)
{
  int* a = (int*)a_;
  printf("%d", *a);
}

int main(void)
{
  list l = lcreate(int);
  lpush_back(l, int, 1);
  lpush_front(l, int, 2);
  lpush_back(l, int, 7);
  //chcemy wstawić 3 między 1 i 7
  literator i = lbegin(l);      //wskazuje na 2
  i = lnext(i);                 //wskazuje na 1
  //wstawia element ZA wskazywanym elemenetem
  linsert(l, int, i, 3);        //3 trafia między 1 i 7
  liter(l, wypisz);             //używamy funkcji iterującej
  //wypiszemy od tyłu, używając for
  //cóż, lista nie jest do tego przystosowana
  //for łądniej wygląda od przodu
  puts("");
  for(i = lprev(lend(l)); i != lprev(lbegin(l)); i = lprev(i))
  {
    printf("%d", lvalue(i, int));
  }
  puts("");
  //wersja wypisywania od przodu
  for(i = lbegin(l); i != lend(l); i = lnext(i))
  {
    //nie polecam tak robić, ale można, jak ktoś nie lubi [lvalue]
    printf("%d", *((int*)i->data));
  }
  ldestroy(&l);
}
