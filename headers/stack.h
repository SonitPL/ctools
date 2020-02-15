#ifndef STACK_H
#define STACK_H

/*
  Adaptacja automatycznej tablicy jako stosu.
*/
#include "autoarray.h"

typedef aarray stack;

/*
  Konstruktor stosu prostego typu danych. 
  Argument: rozmiar pojedynczego elementu.
*/
#define _screate(element_size)\
  _acreate(element_size)

/*
  Konstruktor stosu prostego typu danych.
  Argument: typ pojedynczego elementu.
*/
#define screate(type)\
  _acreate(sizeof(type))

/*
  Konstruktor stosu złożonego typu danych.
  Argumenty: 
    Rozmiar pojedynczego elementu
    Destruktor pojedynczego elementu (domyślnie NULL)
      void (*destructor)(void*)
    Funkcja kopiująca (domyślnie memmove)
      void* (*copier)(void*, const void*, size_t)
*/
#define _screate_complex(element_size, destructor, copier)\
  _acreate_complex(element_size, destructor, copier)

/*
  Konstruktor stosu złożonego typu danych.
  Argumenty takie same jak wyżej, tylko zamiast rozmiaru pojedynczego
  elementu, typ pojedynczego elementu.
*/
#define screate_complex(type, destructor, copier)\
  _acreate_complex(sizeof(type), destructor, copier)

/*
  Destruktor stosu. Argument to wskaźnik na stos.
*/
#define sdestroy(pointer_to_stack)\
  adestroy(pointer_to_stack)

/*
  Usuwa wszystkie elementy ze stosu, wywołując ich destruktor i
  przestawiając liczbę elementów stosu na 0. Nie kasuje stosu, wciąż 
  można na niego wrzucać dane.
*/
#define serase(s)\
  aerase(s)

/*
  Wrzuca element na szczyt stosu korzystając z funkcji kopiującej.
  Argumenty: stos i wskaźnik na kopiowany element.
*/
#define _spush(s, pointer_to_val)\
  _apush(s, pointer_to_val)

/*
  Wrzuca element na szczyt stosu korzystając z funkcji kopiującej.
  Argumenty: stos, typ elementów na stosie, wrzucana wartość
*/
#define spush(s, type, val)\
  do{type spush_help = val; _apush(s, &spush_help);}while(0)

/*
  Zwraca wskaźnik na szczyt stosu.
  Argument: stos
*/
#define _stop(s)\
  _aget(s, asize(s) - 1)

/*
  Zwraca referencję na szczyt stosu.
  Argumenty: stos, typ elementów na stosie
*/
#define stop(s, type)\
  (*((type*)_aget(s, asize(s) - 1)))

/*
  Kasuje element z wierzchu stosu. Wywołuje destruktor.
  Argument: stos
*/
#define spop(s)\
  do{if(s->destructor != NULL)s->destructor(_aget(s, asize(s) - 1));\
  --s->size;}while(0)

/*
  Zwraca liczbę elementów na stosie.
  Argument: stos
*/
#define ssize(s)\
  asize(s)

/*
  Zwraca rozmiar pojedynczego elementu stosu.
  Argument: stos
*/
#define selement_size(s)\
  aelement_size(s)

/*
  Zwraca (int)1, jeśli stos jest pusty. W przeciwnym razie (int)0.
*/
#define sempty(s)\
  aempty(s)

/*
  Zmienia funkcję kopiującą elementów stosu.
  Argumenty: stos, nowa funkcja kopiująca
*/
#define schange_copier(s, newcopier)\
  achange_copier(s, newcopier)

/*
  Zmienia destruktor elementów stosu.
  Argumenty: stos, nowy destruktor
*/
#define schange_destructor(s, newdestructor)\
  achange_destructor(s, newdestructor)

#endif
