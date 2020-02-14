#include "../headers/list.h"

//przerywa program z informacją o błędzie
//argument - nazwa funkcji
#define labort _abort

lelement _lecreate(size_t element_size)
{
  lelement result = malloc(sizeof(struct _lelement));
  if(result == NULL) labort("_lecreate");
  result->data = malloc(element_size);
  if(result->data == NULL) labort("_lecreate");
  result->next = NULL;
  result->prev = NULL;
  return result;
}

void ledestroy(void* el_)
{
  lelement el = *((lelement*)el_);
  free(el->data); //zwalnia WSKAŹNIK na dane, nie same dane
  free(el);
}

int lempty(list l)
{
  return l->begin->next == l->end ? 1 : 0;
}

void* _lhead(list l)
{
  return l->begin->next->data;
}

list lduplicate(list l)
{
  list result = malloc(sizeof(_list));
  if(result == NULL) //błąd malloca
  {
    labort("lduplicate");
  }
  result->element_size = l->element_size;
  result->destructor = l->destructor;
  result->begin = l->begin;
  result->end = l->end;
  return result;
}

void liter(list l, void(*func)(void*))
{
  for(lelement i = l->begin->next; i != l->end; i = i->next)
  {
    func(i->data);
  }
}

list lappend(list first, list last)
{
  list l = lduplicate(first);
  l->end->prev->next = last->begin->next;
  l->end->prev->next->prev = l->end->prev;
  l->end = last->end;
  return l;
}

list _lcreate(size_t element_size)
{
  list l = malloc(sizeof(_list));
  if(l == NULL) labort("_lcreate");
  l->element_size = element_size;
  l->destructor = NULL;
  l->copier = memmove;

  l->begin = malloc(sizeof(struct _lelement));
  l->end   = malloc(sizeof(struct _lelement));
  if((l->begin == NULL) || (l->end == NULL)) labort("_lcreate");
  l->begin->data = NULL;
  l->end->data = NULL;
  l->begin->prev = NULL;
  l->begin->next = l->end;
  l->end->prev = l->begin;
  l->end->next = NULL;

  return l;
}

list _lcreate_complex(size_t element_size, void(*destructor)(void*),
  void*(*copier)(void*, const void*, size_t))
{
  list l = _lcreate(element_size);
  l->destructor = destructor;
  l->copier = copier;
  return l;
}

void ldestroy(void* _l)
{
  list l = *((list*)_l);
  if(l->destructor != NULL)
    liter(l, l->destructor);
  //na razie skasowano tylko wartości pod [data], teraz trzeba skasować
  //same elementy listy - tutaj już nie zadziała iter
  for(lelement i = l->end; i != NULL; )
  {
    lelement temp = i->prev; //trzeba przechować wartość
    ledestroy(&i);
    i = temp;
  }
  free(l);
}

literator lbegin(list l)
{
  return l->begin->next;
}

literator lend(list l)
{
  //czemu tutaj inaczej? Aby ładnie szła pętla for
  //for(literator i = lfirst(l); i != llast(l); i = lnext(i))
  return l->end; 
}

literator lnext(literator i)
{
  if(i->next == NULL) 
  {
    fprintf(stderr,"lnext: Wyjscie poza liste\n");
    abort();
  }
  return i->next;
}

literator lprev(literator i)
{
  if(i->prev == NULL)
  {
    fprintf(stderr,"lprev: Wyjscie poza liste.\n");
    abort();
  }
  return i->prev;
}

void* _lvalue(literator i)
{
  return i->data;
}

list lcopy(list l)
{
  list result = _lcreate_complex(l->element_size, l->destructor,
    l->copier);
  for(literator i = lbegin(l); i != lend(l); i = lnext(i))
  {
    _lpush_back(result, _lvalue(i)); 
  }
  return result;
}

void lremove(list l, literator li)
{
  if((li == l->begin) || (li == l->end))
  {
    fprintf(stderr, "lremove: Proba usuniecia straznika.\n");
    abort();
  }
  literator p = lprev(li);
  literator n = lnext(li);
  p->next = n;
  n->prev = p;
  ledestroy(&li); //nie wywołuje destruktora na danych
}

void lremove_des(list l, literator li)
{
  l->destructor(li->data);//destruktor na danych
  lremove(l, li);
}

void _linsert(list l, literator li, void* val)
{
  lelement newel = _lecreate(l->element_size);
  //old copier
  //memmove(newel->data, val, l->element_size);
  l->copier(newel->data, val, l->element_size);

  newel->next = lnext(li);
  newel->prev = li;
  li->next = newel;
  newel->next->prev = newel;
}

void _lpush_front(list l, void* val)
{
  _linsert(l, l->begin, val);
}

void _lpush_back(list l, void* val)
{
  _linsert(l, l->end->prev, val);
}

