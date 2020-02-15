/*
  Przykład zastosowania funkcji kopiującej.
*/

#include "../../headers/list.h"

/*
  Przykład prostej struktury, w której występuje wskaźnik na dane
  który uniemożliwia zwykłe skopiowanie danych, ponieważ skopiujemy
  wskaźnik, a nie to na co wskaźnik wskazuje.
*/
typedef struct
{
  char* s;
}lol;

//konstruktor
lol create()
{
  lol r;
  r.s = malloc(1024);
  return r;
}

//destruktor
void destroy(void* r_)
{
  lol* r = (lol*)r_;
  free(r->s);
}

/*
  Funkcja kopiująca - domyślna funkcja kopiująca spowodowałaby, że
  edycja wrzucanego obiektu spowodowałaby edycję obiektu na liście.
  Ta implementacja usuwa ten problem poprzez zaalokowanie nowego
  obiektu i przekopiowanie do niego danych.
  Co więcej, nie mamy już problemu postaci: "wywołałem [ldestroy] na
  liście i nagle program mi nie działa, bo wywołał [destroy] na danych
*/
void* copier(void* _dest, const void* _source, size_t element_size)
{
  /*
    Zrzutowanie argumentów, element_size nie jest nam do niczego
    potrzebny, ponieważ znamy obiekt na którym pracujemy. Trzeci
    argument jest niezbędny dla domyślnej funkcji kopiującej.
  */
  lol* dest = (lol*)_dest;
  lol* source = (lol*)_source;
  //alokujemy nowy element
  char* s = malloc(1024);
  dest->s = s;
  //kopiujemy dane
  memcpy(dest->s, source->s, 1024);
  return dest->s;
}


int main(void)
{
  /*
    Tworzymy listę elementów typu lol, z [destroy] jako destruktorem i
    [copier] jako funkcją kopiującą.
  */
  list l = lcreate_complex(lol, destroy, copier);
  //tworzymy elementy, na których chcemy pracować
  lol a = create(); memcpy(a.s, "aaa\0", 4);
  lol b = create(); memcpy(b.s, "bbb\0", 4);
  lol c = create(); memcpy(c.s, "ccc\0", 4);
  //wrzucamy je na tył listy
  lpush_back(l, lol, a);
  lpush_back(l, lol, b);
  lpush_back(l, lol, c);
  /*
    Pokazujemy, że obiekt [a] jest już niezależny od obiektu na liście
  */
  memcpy(a.s, "ddddd\0",6);    
  /*
    Wypisujemy dane listy i zdejmujemy je z listy. Pamięc zwalniamy
    używając destruktora.
    Jeśli używamy [copier] jako funkcji kopiującej, to wynikiem
    będzie:
    aaa
    bbb
    ccc
    Jeśli użyjesz [memmove] lub [memcpy], to uzyskasz
    ddddd
    bbb
    ccc
  */
  printf("%s\n", lvalue(lbegin(l), lol).s); lpop_front_des(l);
  printf("%s\n", lhead(l, lol).s); lpop_front_des(l);
  printf("%s\n", lvalue(lbegin(l), lol).s); lpop_front_des(l);
  //zwalniamy pamięć
  ldestroy(&l);
  /*
    Jeśli użyjesz [memmove] lub [memcpy], to program się w tym
    momencie wysypie, ponieważ te wskaźniki zostały zwolnione wyżej
    Nawet jeśli się nie wysypie, to na pewno valgrind będzie krzyczał.
    "13 allocs, 16 frees" lub coś w tym stylu.
  */
  destroy(&a);
  destroy(&b);
  destroy(&c);
}




