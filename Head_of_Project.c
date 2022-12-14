#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// структура фильма
typedef struct film
{
    int index;
    char name_of_film[100];
    char year_of_production[100];
    char country_of_production[100];
    char genre_of_film[100];
    char rating_of_film[100];
} Film;

// двусвязный список
typedef struct films
{
    Film a_film;
    struct films *prev;
    struct films *next;
} List_of_Films;

// инициализируем первый элемент
List_of_Films *Init_Films(Film a_film)
{
    List_of_Films *list;

    list = (List_of_Films*)malloc(sizeof(List_of_Films));
    list -> a_film = a_film;
    list -> prev = list;
    list -> next = list;

    return(list);
}

// добавляем элемент в список
void Add_Films(List_of_Films *list, Film a_film)
{
    List_of_Films *temp, *temp_p, *temp_prev;
    temp = (List_of_Films*)malloc(sizeof(List_of_Films));
    temp_p = list -> next;
    temp_prev = list -> prev;

    if(temp_prev == NULL){
        list -> prev = list;
    }
    if(temp_prev == list){
        temp_prev = list -> next;
    }

    list -> next = temp;
    temp -> a_film = a_film;
    temp -> next = temp_p;
    temp -> prev = list;
    temp_p -> prev = temp;

}

// вывод списка
void Print_List(List_of_Films *list)
{
    List_of_Films *p;
    p = list;

    do
    {
        printf("%d %s\n", p -> a_film.index, p -> a_film.name_of_film);
        printf("%s\n", p -> a_film.year_of_production);
        printf("%s\n", p -> a_film.country_of_production);
        printf("%s\n", p -> a_film.genre_of_film);
        printf("%s\n\n", p -> a_film.rating_of_film);
        p = p -> prev;
    } while (p != list);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    FILE *open = fopen("C:\\Users\\User\\CLionProjects\\KinoPoisk-on-C\\films.txt", "r");
    Film a_film;
    int index = 1;

    //считываем первый элемент списка и инициализируем список
    a_film.index = index;
    fgets(a_film.name_of_film, 100, open);
    fgets(a_film.year_of_production, 100, open);
    fgets(a_film.country_of_production, 100, open);
    fgets(a_film.genre_of_film, 100, open);
    fgets(a_film.rating_of_film, 100, open);

    List_of_Films* list_of_films = Init_Films(a_film);

    // проходимся до конца файла и добавляем элементы в список
    while(!feof(open))
    {
        Film a_films;
        index++;
        a_films.index = index;
        fgets(a_films.name_of_film, 100, open);
        fgets(a_films.year_of_production, 100, open);
        fgets(a_films.country_of_production, 100, open);
        fgets(a_films.genre_of_film, 100, open);
        fgets(a_films.rating_of_film, 100, open);

        Add_Films(list_of_films, a_films);
    }

    Print_List(list_of_films);

    return 0;
}