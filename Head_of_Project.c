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

//печать карточек с фильмами
void Print_Film(List_of_Films *list){
    List_of_Films *p, *p_next, *p_prev;
    p = list;
    p_prev = list -> next; //следующий и предущий элемент перепутаны?
    p_next = list -> prev;

    //взять название фильма без переноса строки(передлать в функцию?)
    char* copyName;
    char* copyName_next;
    char* copyName_prev;
    copyName = copyString(p -> a_film.name_of_film);
    copyName_next = copyString(p_next -> a_film.name_of_film);
    copyName_prev = copyString(p_prev -> a_film.name_of_film);

    printf("________________________________________      ________________________________________\n");
    printf("|");

    //длина названия фильма (предыдущий)
    int sizeNameRightPrev;
    sizeNameRightPrev = strlen (p_prev -> a_film.name_of_film); //количество символов неправильное(буква за 2 символа, остальное за 1)
    char probelName = '\x20';
    char plusName = '\x2B';
    char oneName ='\x31';
    char comaName ='\x2C';
    char *s;
    char *c;
    char *z;
    char *x;
    int countSingleLetter = 0;
    s = strchr(p_prev -> a_film.name_of_film, probelName);
    c = strchr(p_prev -> a_film.name_of_film, plusName);
    z = strchr(p_prev -> a_film.name_of_film, oneName);
    x = strchr(p_prev -> a_film.name_of_film, comaName);
    //несколько while, т.к. в одном выдаёт неправильный результат(переделать?)
    while (s != NULL){
        countSingleLetter++;
        s = strchr(s+1, probelName);
    }
    while (c != NULL){
        countSingleLetter++;
        c = strchr(c+1, plusName);
    }
    while (z != NULL){
        countSingleLetter++;
        z = strchr(z+1, oneName);
    }
    while (x != NULL){
        countSingleLetter++;
        x = strchr(x+1, comaName);
    }
    sizeNameRightPrev = (sizeNameRightPrev+countSingleLetter)/2; //настоящая длина названия фильма
    int restNameSizePrev = (40-sizeNameRightPrev)/2; //для прописывания пробелов перед\после названия

    if(sizeNameRightPrev == 40){ //если фильм длинный, то без пробелов
        printf("%s", copyName_prev);
    }
    else {
        for (int i = 1; i < restNameSizePrev; i++) {//пробелы перед названием
            printf(" ");
        }
        if (sizeNameRightPrev % 2 == 1 && strlen(p_prev->a_film.name_of_film) % 2 == 0) {//для более ровного вывода
            printf("  ");
        }
        else if (sizeNameRightPrev % 2 == strlen(p_prev->a_film.name_of_film) % 2) {//для более ровного вывода
            printf(" ");
        }
        printf("%s", copyName_prev);//название(предыдущее)

        int odd = 0;
        for (int i = 0; i < restNameSizePrev; i++) {//пробелы после названия
            if (strlen(p_prev->a_film.name_of_film) % 2 == 0 && odd == 0) {//если кол-во символов чётно, то на 1 пробел меньше
                odd++;
            }
            else {
                printf(" ");
            }
        }
    }

    printf("|    |");

    //длина названия фильма (следующий)
    int sizeNameRightNext;
    sizeNameRightNext = strlen (p_next -> a_film.name_of_film);

    countSingleLetter = 0;
    s = strchr(p_next -> a_film.name_of_film, probelName);
    c = strchr(p_next -> a_film.name_of_film, plusName);
    z = strchr(p_next -> a_film.name_of_film, oneName);
    x = strchr(p_next -> a_film.name_of_film, comaName);
    while (s != NULL){
        countSingleLetter++;
        s = strchr(s+1, probelName);
    }
    while (c != NULL){
        countSingleLetter++;
        c = strchr(c+1, plusName);
    }
    while (z != NULL){
        countSingleLetter++;
        z = strchr(z+1, oneName);
    }
    while (x != NULL){
        countSingleLetter++;
        x = strchr(x+1, comaName);
    }
    sizeNameRightNext = (sizeNameRightNext+countSingleLetter)/2;
    int restNameSizeNext = (40-sizeNameRightNext)/2;
    if(sizeNameRightNext == 40){
        printf("%s", copyName_next);
    }
    else {
        for (int i = 1; i < restNameSizeNext; i++) {
            printf(" ");
        }
        if (sizeNameRightNext % 2 == 1 && strlen(p_next->a_film.name_of_film) % 2 == 0){
            printf("  ");
        }
        else if (sizeNameRightNext % 2 == strlen(p_next->a_film.name_of_film) % 2){
            printf(" ");
        }
        printf("%s", copyName_next);//название(следующее)
        int odd = 0;
        for (int i = 0; i < restNameSizeNext; i++){
            if (strlen(p_prev->a_film.name_of_film) % 2 == 0 && odd == 0) {
                odd++;
            } else {
                printf(" ");
            }
        }
    }

    printf("|\n");
    printf("|                      ________________________________________                      |\n"); //40 символов

    //длина названия фильма (выбранный)
    int sizeNameRight;
    sizeNameRight = strlen (p -> a_film.name_of_film);

    countSingleLetter = 0;
    s = strchr(p -> a_film.name_of_film, probelName);
    c = strchr(p -> a_film.name_of_film, plusName);
    z = strchr(p -> a_film.name_of_film, oneName);
    x = strchr(p -> a_film.name_of_film, comaName);
    while (s != NULL){
        countSingleLetter++;
        s = strchr(s+1, probelName);
    }
    while (c != NULL){
        countSingleLetter++;
        c = strchr(c+1, plusName);
    }
    while (z != NULL){
        countSingleLetter++;
        z = strchr(z+1, oneName);
    }
    while (x != NULL){
        countSingleLetter++;
        x = strchr(x+1, comaName);
    }
    sizeNameRight = (sizeNameRight+countSingleLetter)/2;//длина названия фильма
    printf("|______________________|");
    int restNameSize = (40-sizeNameRight)/2;//считаем пробелы перед/после названия
    if(sizeNameRight == 40){
        printf("%s", copyName);
    }
    else {
        for (int i = 1; i < restNameSize; i++) {//пробелы перед названием
            printf(" ");
        }
        if (sizeNameRight % 2 == 1 && strlen(p->a_film.name_of_film) % 2 == 0) {
            printf("  ");
        } else if (sizeNameRight % 2 == strlen(p->a_film.name_of_film) % 2) {
            printf(" ");
        }
        printf("%s", copyName);//печать названия выбранного фильма
        int odd = 0;
        for (int i = 0; i < restNameSize; i++) {//пробелы после названия
            if (strlen(p->a_film.name_of_film) % 2 == 0 && odd == 0) {
                odd++;
            } else {
                printf(" ");
            }
        }
    }

    printf("|_____________________|\n");
    printf("                       |");

    //рейтинг в виде звёзд
    char *ratingCurrent = p -> a_film.rating_of_film;
    float Num = atof(ratingCurrent);
    printf("              ");
    for(int i=1; i<11; i++){
        if(Num > i){
            printf("\u2605");
        }
        else if(Num < i){
            printf("\u2606");
        }
    }
    printf("            ");
    printf("|");
    printf("\n                       |_______________________________________|\n");
    printf("                       \u2B05                                     \u27A1\n"); //стрелки для красоты
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

    //Print_List(list_of_films);
    
    Print_Film(list_of_films);

    return 0;
}
