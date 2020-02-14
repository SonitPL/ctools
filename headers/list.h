#ifndef LIST_H
#define LIST_H
/*
  Implementacja dwukierunkowej listy.
*/

#include "commons.h"

/*
  Struktura pojedynczego elementu wewnątrz listy.
*/
struct _lelement
{
  //przechowywana zmienna
  void* data;
  //wskaźnik na następny element
  struct _lelement* next;
  //wskaźnik na poprzedni element
  struct _lelement* prev;
};
typedef struct _lelement* lelement;

/*
  Konstruktor pojedynczego elementu BEZ USTAWIENIA WARTOŚCI
*/
lelement _lecreate(size_t);

/*
  Destruktor pojedynczego elementu.
*/
void ledestroy(void*);

/*
  Struktura samej listy.
*/
typedef struct
{
  //rozmiar pojedynczego elementu
  size_t element_size;
  //destruktor pojedynczego elementu
  void (*destructor)(void*);
  //funkcja kopiująca - domyślnie memmove
  void* (*copier)(void*, const void*, size_t);
  //strażnik z przodu
  lelement begin;
  //strażnik z tyłu
  lelement end;
} _list;
typedef _list* list;

/*
  Zwraca wartość niezerową, jeśli lista jest pusta.
*/
int lempty(list);

/*
  Zwraca wskaźnik na pierwszy element listy.
  NIE [_lelement], ten typ jest pomocniczy, ale [lelement->data].
  W innej części kodu zostanie zdefiniowane makro [lhead] , które upraszcza 
  użycie tej funkcji.
  Jeśli lista jest pusta, to program powinien zwrócić NULL (o ile ktoś nie
  grzebał przy l->end)
  Czemu nie ma [ltail]? Bo generuje on za dużo potencjalnych błędów, na przykład
  nagła zmiana listy w jednokierunkowe drzewo, którego nie ma jak sensownie
  usunąć.
*/
void* _lhead(list);
/*
  Zwrócę uwagę, że poniższe makro umożliwia polecenie: lhead(l,int) = 69; 
  W normalnym C nie ma to sensu, tutaj ma. Pod głowę listy można podstawić
  w ten sposób inną wartość.
*/
#define lhead(l, type)\
  (*(type*)_lhead(l))

/*
  Zwraca identyczną listę, NIE JEST TO KOPIA. Zwrócona lista jest tożsama z 
  listą daną jako argument. Edycja elementów jednej, edytuje drugą.
*/
list lduplicate(list);

/*
  Funkcja wywołuje funkcję daną jako argument na wszystkich elementach listy.
  Funkcja musi przyjmować void* (wskaźnik na edytowany element, zrzutować 
  trzeba w środku funkcji) i zwracać void.
*/
void liter(list, void(*func)(void*));

/*
  Dodaje pojedynczy element z przodu listy.
  Argument: wskaźnik na element do dodania.
*/
void _lpush_front(list, void*);
#define lpush_front(l, type, val)\
 do{type _lpush_macro_g4rB4ge = val; _lpush_front(l, &_lpush_macro_g4rB4ge);}\
 while(0)

/*
  Dodaje pojedynczy element z tyłu listy.
  Argumenty jak w _ladd_front
*/
void _lpush_back(list, void*);
#define lpush_back(l, type, val)\
 do{type _lpush_macro_g4rB4ge = val; _lpush_back(l, &_lpush_macro_g4rB4ge);}\
 while(0)

/*
  Zwraca listę będącą połączeniem dwóch list.
  UWAGA! Połączenie przez referencję, innymi słowy elementy nie są kopiowane.
  Powoduje to, że edycja wartości na powstałej liście, spowoduje edycję na
  pierwotnych listach.
*/

list lappend(list, list);

/*
  Tworzy pustą listę prostego typu danych.
*/
list _lcreate(size_t);
#define lcreate(type)\
  _lcreate(sizeof(type))

/*
  Tworzy pustą listę złożonego typu danych.
*/
list _lcreate_complex(size_t, void(*destructor)(void*), 
  void*(*copier)(void*, const void*, size_t));
#define lcreate_complex(type, destructor, copier)\
  _lcreate_complex(sizeof(type), destructor, copier)

/*
  Destruktor listy. Wywołuje destruktor na wszystkich elementach listy.
  Zwrócę uwagę na niebezpieczeństwo, jeśli mamy kilka list, które gdzieś się
  rozgałęziają (jakimś cudem) , ale mają część wspólną. Zniszczenie jednej 
  listy spowoduje zniszczenie fragmentu drugiej. Co więcej takie działanie
  niszczy sens elementów [prev] i [next]. Dlatego stanowczo odradza się takich
  działań na listach.
*/
void ldestroy(void*);


//typ iteratora
typedef lelement literator;
/*
  Zwraca wskaźnik na I element - ELEMENT, aby wskaźnik na wartość, 
  użyj [_lvalue]
*/
literator lbegin(list);

/*
  Zwraca wskaźnik na element ZA OSTATNIM - czyli na strażnika.
*/
literator lend(list);

/*
  Zwróć następny element listy. Jeśli nie istnieje, przerwij program.
*/
literator lnext(literator);

/*
  Zwróc poprzedni element listy. Jeśli nie istnieje, przerwij program.
*/
literator lprev(literator);

/*
  Zwraca wskaźnik na wartość, na którą wskazuje iterator. Aby działać wygodnie,
  użyj makra [lvalue]
*/
void* _lvalue(literator);
#define lvalue(i, type)\
  (*((type*)_lvalue(i)))

/*
  Zwraca dokłądną kopię listy. Kopiuje zgodnie z przekazaną funkcją
  kopiującą.
*/
list lcopy(list);

/*
  Usuwa element z listy. Próba usunięcia strażnika zakończy się
  wywołaniem [abort].
  NIE WYWOŁUJE DESTRUKTORA NA DANYCH!
*/
void lremove(list l, literator li);
//
#define lpop_back(l)\
  lremove(l, lprev(lend(l)))
#define lpop_front(l)\
  lremove(l, lbegin(l))

//wersja lremove, która wywołuje destruktor na danych
void lremove_des(list l, literator li);
#define lpop_back_des(l)\
  lremove_des(l, lprev(lend(l)))
#define lpop_front_des(l)\
  lremove_des(l, lbegin(l))


/*
  Dodaje element do listy PO elemencie wskazywwanym iteratorem.
  Jeśli iterator wskazuje na strażnika końca: [abort]
*/
void _linsert(list l, literator li, void* val);
#define linsert(l, type, li, val)\
  do{type _linsert_g4rB4ge = val; _linsert(l, li, &_linsert_g4rB4ge);} while(0)

#endif
