#ifndef DEQUE_H
#define DEQUE_H

/*
  Adaptacja listy jako dwustronnej kolejki.
*/
#include "list.h"

typedef list deque;
/*
  Konstruktor kolejki prostego typu danych. Jako argument przyjmuje 
  rozmiar pojedynczego elementu.
*/
#define _dqcreate(element_size)\
  _lcreate(element_size)
#define dqcreate(type)\
  _lcreate(sizeof(type))

/*
  Konstruktor kolejki złożonego typu danych.
  II argument to destruktor
  III argument to funkcja kopiująca.
*/
#define _dqcreate_complex(element_size, destructor, copier)\
  _lcreate_complex(element_size, destructor, copier)
#define dqcreate_complex(type, destructor, copier)\
  _lcreate_complex(sizeof(type), destructor, copier)

/*
  Funkcja zwracająca wartość niezerową, gdy kolejka jest pusta.
*/
#define dqempty(dq)\
  lempty(dq);

/*
  Zwraca wskaźnik na I element.
*/
#define _dqfront(dq)\
  _lvalue(lbegin(dq))
#define dqfront(dq, type)\
  (*((type*)_dqfront(dq)))

/*
  Zwraca wskaźnik na ostatni element
*/
#define _dqback(dq)\
  _lvalue(lprev(lend(dq)));
#define dqback(dq, type)\
  (*((type*)_dqback(dq)))

/*
  Wrzuca element na początek kolejki. II argument to wskaźnik na
  wrzucaną wartość. Użyj makra [dqpush_front], aby wrzucać wartości.
*/
#define _dqpush_front(dq, val)\
  _lpush_front(dq, val);
#define dqpush_front(dq, type, val)\
  do{type _push_macro_1245y = val; _lpush_front(dq, \
    &_push_macro_1245y);}while(0)

/*
  Wrzuca element na koniec kolejki. II argument to wskaźnik na
  wrzucaną wartość. Użyj makra [dqpush_back], aby wrzucać wartości.
*/
#define _dqpush_back(dq, val)\
  _lpush_back(dq, val);
#define dqpush_back(dq, type, val)\
  do{type _push_macro_1245y = val; _lpush_back(dq, \
    &_push_macro_1245y);}while(0)

/*
  Kasuje element z końca kolejki. NIE WYWOŁUJE DESTRUKTORA!
  Próba usunięcia z pustej kolejki zakończy się [abort]
*/
#define dqpop_back(dq)\
  lremove(dq, lprev(lend(dq)))

//to samo co wyżej, ale wywołuje destruktor
#define dqpop_back_des(dq)\
  lremove_des(dq, lprev(lend(dq)))

/*
  Kasuje element z początku kolejki. NIE WYWOŁUJE DESTRUKTORA!
  Próba usunięcia z pustej kolejki zakończy się [abort]
*/
#define dqpop_front(dq)\
  lremove(dq, lbegin(dq))

//to samo co wyżej, ale wywołuje destruktor
#define dqpop_front_des(dq)\
  lremove_des(dq, lbegin(dq))

/*
  Destruktor kolejki.
*/
#define dqdestroy(dq)\
  ldestroy(dq)

#endif
