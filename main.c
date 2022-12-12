#include <stdio.h>
#include <stdlib.h>

typedef struct film
{
  char* name_of_film;
  int year_of_production;
  char* country_of_production;
  char* genre_of_film;
  double rating_of_film;

  struct list *prev;
  struct list *next;
} Film;

Film* Create_Film(char* name, int year, char* country, char* genre, double rating)
{
  Film *a_film;
  a_film = (Film*)malloc(sizeof(Film));

  a_film -> name_of_film = name;
  a_film -> year_of_production = year;
  a_film -> country_of_production = country;
  a_film -> genre_of_film = genre;
  a_film -> rating_of_film = rating;
  a_film -> next = NULL;
  a_film -> prev = NULL;

  return(a_film);
}

Film* Add_Film(Film *films, Film *a_film)
{
  
}

int main()
{
  
}