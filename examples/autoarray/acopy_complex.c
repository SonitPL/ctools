/*
  Przykład użycia [acopy] przy złożonej strukturze.
  W tym przypadku, tablica tablic
*/
#include "../../headers/autoarray.h"

int main(void)
{
  aarray tab = acreate_complex(aarray, adestroy, acopy);
  /*
    Ze względu na zdefiniowany operator kopiowania, musimy zdefiniować
    pustą tablicę, którą będziemy wrzucać - nie możemy użyć 
    konstruktora wewnątrz wywołania, ponieważ otrzymany wynik
    zostanie skopiowany i powstanie wyciek pamięci.
    Można tego uniknąć poprzez zmianę funkcji kopiującej. Inicjujemy
    tablicę z [memmove], a następnie zmieniamy funkcję na [acopy].
    Jako, że ten przykład ma na celu prezentację [acopy], użyto
    pierwszego rozwiązania.
    Ewentulaną zmianę funkcji kopiującej dokonuje się przy pomocy:
    [achange_copier].
  */
  aarray empty = acreate(int);
  for(int i = 0; i < 3; ++i)//wrzucamy kopie pustej tablicy na tablicę
    apush(tab, aarray, empty);    
  //kasujemy pustą tablicę
  adestroy(&empty);
  for(int i = 0; i < 3; ++i)
  {
    for(int j = 0; j < 3; ++j)
    {
      apush(aget(tab, aarray, i), int, i + j);
    }
  }
  /*
    Tablica ma postać:
    0 1 2
    1 2 3
    2 3 4
  */
  puts("Oryginal:");
  for(int i = 0; i < 3; ++i)
  {
    for(int j = 0; j < 3; ++j) printf("%d ", aget(
      aget(tab, aarray, i), int, j));
    puts("");
  }
  //kopiujemy tę tablicę
  aarray tab_copy = NULL;
  acopy(&tab_copy, &tab, 42/*does not matter*/);
  //edytujemy kopię
  aget(aget(tab_copy, aarray, 1), int, 1) = 8;
  //wypisujemy zedytowaną kopię tablicy 
  puts("Zedytowana kopia:");
  for(int i = 0; i < 3; ++i)
  {
    for(int j = 0; j < 3; ++j) printf("%d ", aget(
      aget(tab_copy, aarray, i), int, j));
    puts("");
  }
  //i oryginał, by pokazać, że nie uległ zmianie
  puts("\n\nOryginal nie ulegl zmianie:");
  for(int i = 0; i < 3; ++i)
  {
    for(int j = 0; j < 3; ++j) printf("%d ", aget(
      aget(tab, aarray, i), int, j));
    puts("");
  }
  printf("Pokazuje to, ze [acopy] wywolalo rowniez operator"
    " kopiowania nizej, dzieki czemu rowniez tablice nizej zostaly "
    "skopiowane\n");
  
  //grzecznie zwalniamy obie tablice
  adestroy(&tab);
  adestroy(&tab_copy);
}
