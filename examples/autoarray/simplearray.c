/*
  Przykład tablicy prostego typu danych.
*/
#include "../../headers/autoarray.h"

int main(void)
{
  aarray tab = acreate(int);
  if(aempty(tab))
  {
    apush(tab, int, 2);
    apush(tab, int, 1);
    apush(tab, int, 3);
    apush(tab, int, 7);
    printf("Rozmiar: %ld\n", asize(tab));
    printf("Maksymalna liczba elementow: %ld\n", acapacity(tab));
    printf("Rozmiar pojedynczego elementu: %ld\n", aelement_size(tab));
    printf("Pierwszy element to: %d\n", *abegin(tab, int));
    printf("Ostatni element to: %d\n", *(aend(tab, int) - 1));
    aset(tab, int, asize(tab) - 1, 42);
    printf("Teraz ostatni element to: %d\n", aend(tab, int)[-1]);
    printf("Pierwszy element to wciaz: %d\n", aget(tab, int, 0));
    printf("Srodkowy element to: %d\n",abegin(tab, int)[asize(tab) >> 1]);
    aerase(tab);
    printf("Teraz tablica ma: %ld elementow\n", asize(tab));
    printf("Ale pojemnosc wciaz wynosi: %ld\n", acapacity(tab));
    puts("Teraz przepelnijmy tablice:");
    for(int i = 0; i < 65; ++i) apush(tab, int, 0);
    printf("Teraz tablica ma: %ld elementow\n", asize(tab));
    printf("Ale pojemnosc teraz wynosi: %ld\n", acapacity(tab));
  }
  else
  {
    printf("Jakim cudem dopiero co zadeklarowana tablica ma w "
    "sobie elementy?\n");
  }
  printf("Teraz wywolujemy destruktor tablicy, by zwolnic pamiec.\n");
  adestroy(&tab);  
}
