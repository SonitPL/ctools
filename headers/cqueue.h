#ifndef CQUEUE_H
#define CQUEUE_H

#include "deque.h"

/*
  Adaptacja kolejki jako szczególnego przypadku kolejki dwustronnej,
  a tym samym listy.
*/

typedef list queue;

/*
  Konstruktor kolejki prostego typu danych. Jako argument przyjmuje 
  rozmiar pojedynczego elementu.
*/
#define _qcreate(element_size)\
  _lcreate(element_size)
#define qcreate(type)\
  _lcreate(sizeof(type))

/*
  Konstruktor kolejki złożonego typu danych.
  II argument to destruktor
  III argument to funkcja kopiująca
*/
#define _qcreate_complex(element_size, destructor, copier)\
  _lcreate_complex(element_size, destructor, copier)
#define qcreate_complex(type, destructor, copier)\
  _lcreate_complex(sizeof(type), destructor, copier)

/*
  Funkcja zwracająca wartość niezerową, gdy kolejka jest pusta.
*/
#define qempty(q)\
  lempty(q)

/*
  Zwraca wskaźnik na I element.
*/
#define _qfront(q)\
  _lvalue(lbegin(q))
#define qfront(q, type)\
  (*((type*)_qfront(q)))

/*
  Wrzuca element na koniec kolejki. II argument to wskaźnik na
  wrzucaną wartość. Użyj makra [qpush], aby uzyskać wartość.
*/
#define _qpush(q, val)\
  _lpush_back(q, val);
#define qpush(q, type, val)\
  do{type _push_macro_1245y = val; _lpush_back(q, \
    &_push_macro_1245y);}while(0)

/*
  Kasuje element z początku kolejki. NIE WYWOŁUJE DESTRUKTORA!
  Próba usunięcia z pustej kolejki zakończy się [abort]
*/
#define qpop(q)\
  lremove(q, lbegin(q))

//to samo co wyżej, ale wywołuje destruktor
#define qpop_des(q)\
  lremove_des(q, lbegin(q))

/*
  Destruktor kolejki.
*/
#define qdestroy(q)\
  ldestroy(q)

#endif
