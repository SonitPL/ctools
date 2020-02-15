#include "../headers/autoarray.h"

size_t asize(aarray a)
{
  return a->size;
}

size_t acapacity(aarray a)
{
  return a->capacity;
}

size_t aelement_size(aarray a)
{
  return a->element_size;
}

int aempty(aarray a)
{
  return a->size == 0 ? 1 : 0;
}

void* _abegin(aarray a)
{
  return a->data;
}

void* _aend(aarray a)
{
   return a->data + a->element_size * a->size;
}

void* _aget(aarray a, size_t index)
{
  if( index >= a->size ) 
    report_error("_aget", "Index out of bounds.");
  return a->data + a->element_size * index;
}

void _aset(aarray a, size_t index, void* source)
{
  void* dest = _aget(a, index);
  a->copier(dest, source, a->element_size);
}

void aresize(aarray a, size_t new_capacity)
{
  //jeśli wektor nie został jeszcze zaalokowany - zaalokuj
  if(a->data == NULL)
  {
    a->capacity = new_capacity;
    a->data = malloc(new_capacity * a->element_size);
    //błąd malloca
    if(a->data == NULL)
    {
      _abort("aresize");
    }
  }
  else
  {
    //dokonaj realokacji
    a->capacity = new_capacity;
    a->data = realloc(a->data, new_capacity * a->element_size);
    if(a->data == NULL) _abort("aresize");
  }
}

void _apush(aarray a, void* source)
{
  //brakuje miejsca - zwiększ pojemność
  if(a->size >= a->capacity || a->data == NULL)
  {
    aresize(a, a->capacity << 1 );
  }
  ++a->size;
  _aset(a, a->size - 1, source);
}

void aerase(aarray a)
{
  if(a->destructor != NULL)
  {
    for( size_t i = 0; i < a->size; ++i)
    {
      a->destructor(a->data + a->element_size * i);  
    }
  }
  a->size = 0;
}

aarray _acreate(size_t element_size)
{
  aarray a = malloc(sizeof(_aarray));
  //błąd malloca
  if(a == NULL)
  {
    _abort("_acreate");
  }
  a->size = 0;
  a->element_size = element_size;
  a->capacity = 16;
  a->data = NULL;
  a->destructor = NULL;
  a->copier = memmove;
  return a;
}

aarray _acreate_complex(size_t element_size, void (*destructor)(void*)
, void* (*copier)(void*, const void*, size_t))
{
  aarray a = _acreate(element_size);
  a->destructor = destructor;
  a->copier = copier;
  return a;
}

void adestroy(void* _a)
{ 
  aarray a = *((aarray*)_a);
  aerase(a);
  free(a->data);
  a->data = NULL;
  free(a);
}

void* acopy(void* _dest, const void* _source, size_t element_size)
{
  aarray* dest = (aarray*)_dest;
  aarray* source = (aarray*)_source;
  //alokujemy miejsce na nową tablicę
  aarray result = malloc(sizeof(_aarray));
  //kopiujemy source - skopiowane zostaną wszystkie pola
  memcpy(result, *source, sizeof(_aarray));
  //trzeba będzie zmodyfikować pola: [data] i [size]
  result->data = NULL; result->size = 0;
  result->data = malloc(acapacity(*source) * aelement_size(*source));
  //zaalokowana pamięć na tablicę, więc teraz iterujemy się po
  //całej tablicy *source i robimy [_apush] w result
  for( size_t i = 0; i < asize(*source); ++i)
  {
    _apush(result, _aget(*source, i));
  }
  //pole, na które wskazuje WSKAŹNIK [result] jest już w pełni
  //zainicjowane, teraz trzeba podstawić ten WSKAŹNIK pod
  //WSKAŹNIK na WSKAŹNIK _dest
  *dest = result;
  return result;        //to nie ma znaczenia, co jest zwracane 
}

void achange_copier(aarray a, void* (*newcopier)(void*, const void*, size_t))
{
  a->copier = newcopier;
}

void achange_destructor(aarray a, void (*newdestructor)(void*))
{
  a->destructor = newdestructor;
}
