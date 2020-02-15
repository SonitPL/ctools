#ifndef AUTOARRAY_H
#define AUTOARRAY_H

#include "commons.h"

/*
  Struktura, utrzymująca tablicę z pewną liczbą elementów.
  Tablicę można powiększać o 1 element przy pomocy makra [apush_back],
  jeśli w aktualnie zaalokowanej tablicy zabraknie miejsca to 
  automatycznie zostanie zaalokowana nowa tablica, 2 razy większa 
  przy pomocy [realloc]. Z tego powodu nie należy pamiętać 
  bezpośrednich wskaźników na elementy tablicy, ponieważ mogą przestać
  działać. Proszę korzystać z makr [abegin] i [aend], które zwracają 
  wskaźniki na początek i koniec tablicy, lub makra [aget], które
  zwraca referencję na dany element tablicy.

  Domyślnie alokowane jest miejsce na 16 elementów. Jeśli chcesz to 
  zmienić, użyj [aresize].

  Konstruktor tablicy prostych struktur:  makro [acreate] 
  Konstruktor tablicy złożonych struktur: makro [acreate_complex]
  Destruktor: makro [adestroy]
  Funkcja kopiująca: [acopy]

  Jeśli alokowany typ danych wymaga destruktora, to należy użyć 
  konstruktora: [acreate_complex], który wymaga dodatkowo wskaźnika na
  funkcję, która jest destruktorem oraz na funkcję kopiującą element.
*/
typedef struct
{
  //liczba elementów
  size_t size;
  //rozmiar pojedynczego elementu
  size_t element_size;
  //aktualna pojemność tablicy z danymi ,LICZBA ELEMENTÓW, nie BAJTÓW!
  size_t capacity;
  //tablica z danymi
  void* data;
  //destruktor - jeśli struktura nie ma destruktora, dajesz tu NULL
  void (*destructor)(void*);
  /*
    Funkcja kopiująca dla elementów tablicy, domyślnie [memmove]
    wykorzystywana gdy wrzucasz element do tablicy lub zmieniasz
    wartość pola poprzez [aset], nie działa gdy dokonujesz zmiany
    wartości pola w inny sposób, np. abegin(tab, int)[0] = 1
  */
  void* (*copier)(void*, const void*, size_t);
} _aarray;

//do wszystkich działań na tej strukturze, proszę używać tego typu
typedef _aarray* aarray;

//funkcja zwracająca liczbę elementów w tablicy
size_t asize(aarray);

//funkcja zwracająca aktualną maksymalną pojemność tablicy
size_t acapacity(aarray);

//funkcja zwracająca rozmiar pojedynczego elementu
size_t aelement_size(aarray);

//funkcja zwracająca 1, jeśli tablica jest pusta
int aempty(aarray);

//funkcja zwracająca wskaźnik na I element tablicy
void* _abegin(aarray);
/*
  Zwraca wskaźnik na pierwszy element tablicy - od razu zrzutowany na 
  odpowiedni typ, więc można łatwo odnosić się do elementów przez 
  operator [], np: abegin(a, int)[3] = 4. Takie podstawianie jednak ma
  wadę, że nie zostaje wywołana funkcja kopiująca, jak przy użyciu
  [aset].
*/
#define abegin(a, type)\
  ((type*)_abegin(a))

//zwraca adres elementu o indeksie index (indeksowanie od 0)
void* _aget(aarray, size_t);
/*
  Makro zwraca referencję zamiast wskaźnika na wartość, więc można 
  robić np: aget(a, int, 0) = 21;
*/
#define aget(a, type, index)\
  *((type*)_aget(a, index))


/*
  Zwraca wskaźnik na element bezpośrednio ZA ostatnim. Nie polecam 
  próbować pod niego coś podstawiać, lub robić z nim coś innego. 
  Służy raczej do pętli, typu:
  for(int* i = abegin(a, int); i != aend(a, int); ++i);
*/
void* _aend(aarray);
#define aend(a, type)\
  ((type*)_aend(a))


/*
  Kopiuje wartość, do której wskaźnik jest dany jako III argument do
  komórki tablicy, której indeks jest dany jako II argument.
  Wykorzystuje do tego funkcję kopiującą ustawioną w tablicy.
*/

void _aset(aarray, size_t, void*);
/*
  Makro podstawia wartość pod indeks w pamięci, więc można robić np:
  aset(a, int, 0, 42); - w tablicy a, podstaw 42 na indeksie 0
*/
#define aset(a, type, index, val)\
  do{type aset_help = val; _aset(a, index, &aset_help);}while(0)



/*
  Zmienia rozmiar tablicy - domyślnie wykorzystywana przez _apush
  ale nikt nie broni używania jej przez użytkownika.
*/
void aresize(aarray, size_t);

/*
  Wrzuca element na koniec tablicy i rozszerza ją, jeśli brakuje 
  miejsca.
*/
void _apush(aarray, void*);
#define apush(a, type, val)\
  do{type apush_help = val; _apush(a, &apush_help);}while(0)

/*
  Oczyszcza tablicę - oznacza wszystkie elementy jako usunięte 
  (i wywołuje na  nich destruktor), ale nie zmniejsza już zaalokowanej pamięci
*/
void aerase(aarray);

/*
  Konstruktor tablicy prostego typu danych. Jako argument przyjmuje 
  rozmiar pojedynczego elementu.
  Domyślnie [_acreate] alokuje miejsce na 16 elementów.
*/
aarray _acreate(size_t);
#define acreate(type)\
  _acreate(sizeof(type))

/*
  Konstruktor tablicy złożonego typu danych. Oprócz rozmiaru 
  pojedynczego elementu, przyjmuje również wskaźnik na destruktor i
  na funkcję kopiującą elementy.
*/
aarray _acreate_complex(size_t, void (*destructor)(void*),
  void* (*copier)(void*, const void*, size_t));
#define acreate_complex(type, destructor, copier)\
  _acreate_complex(sizeof(type), destructor, copier)

/*
  Destruktor tablicy. Kompatybilny z destruktorem jej elementów.
  Więc jak chcesz zrobić tablicę tablic, to możesz dać [adestroy] jako
  argument do [acreate_complex].
  Typ argumentu: aarray*
*/
void adestroy(void*);

/*
  Funkcja kopiująca dla automatycznej tablicy. Kopiując tablicę
  wywołuje funkcję kopiującą na niższych poziomach!
  Typy argumentów: aarray*, const aarray*, size_t
*/
void* acopy(void*, const void*, size_t);

/*
  Funkcja zmieniająca funkcję kopiującą.
*/
void achange_copier(aarray, void* (*newcopier)(void*, const void*, size_t));

/*
  Funkcja zmieniająca destruktor.
*/
void achange_destructor(aarray, void (*newdestructor)(void*));

#endif
