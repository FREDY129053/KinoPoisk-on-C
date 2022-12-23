#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <windows.h> // for GetKeyState function

// Функция для скрытия курсора
void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

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
        temp_prev = list->next;
    }

    list -> next = temp;
    temp -> a_film = a_film;
    temp -> next = temp_p;
    temp -> prev = list;
    temp_p -> prev = temp;

}

// Вывод списка
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

// Взять строку в файле без переноса на следующую
char* copyString(char s[]){
    char* s2;
    s2 = (char*)malloc(100);

    strcpy(s2, s);
    s2[strlen(s2)-1] = 0;
    return (char*)s2;
}

// Печать карточек с фильмами
void Print_Film(List_of_Films *list, int Position){ // Position -1, 0, 1
    List_of_Films *point, *pointNext, *pointPrev;
    if (Position == 0) {
        point = list;
        pointPrev = list->next; // следующий и предущий элемент перепутаны?
        pointNext = list->prev;
    } else if (Position == -1) {
        point = list->prev;
        pointPrev = list;
        pointNext = list->prev->prev;
    } else if (Position == 1) {
        point = list->next;
        pointPrev = list->next->next;
        pointNext = list;
    }


    // Взять название фильма без переноса строки(передать в функцию?)
    char* copyName;
    char* copyName_next;
    char* copyName_prev;
    copyName = copyString(point -> a_film.name_of_film);
    copyName_next = copyString(pointNext -> a_film.name_of_film);
    copyName_prev = copyString(pointPrev -> a_film.name_of_film);

    printf("╔══════════════════════════════════════╗    ╔════════════════════════════════════════╗\n");
    printf("║");

    // Длина названия фильма (предыдущий)
    int sizeNameRightPrev;
    sizeNameRightPrev = strlen(pointPrev -> a_film.name_of_film); // Количество символов неправильное(буква за 2 символа, остальное за 1)
    char spaceName = ' ', plusName = '+', oneName ='1', commaName = ',';
    char *spaceChar, *plusChar, *oneChar, *commaChar;

    int countSingleLetter = 0;
    spaceChar = strchr(pointPrev -> a_film.name_of_film, spaceName);
    plusChar = strchr(pointPrev -> a_film.name_of_film, plusName);
    oneChar = strchr(pointPrev -> a_film.name_of_film, oneName);
    commaChar = strchr(pointPrev -> a_film.name_of_film, commaName);

    // Несколько while, т.к. в одном выдаёт неправильный результат(переделать?)
    // Переделал в один цикл(трахать?)
    while (1) {
        if (spaceChar != NULL) {
            countSingleLetter++;
            spaceChar = strchr(spaceChar + 1, spaceName);
        }

        if (plusChar != NULL) {
            countSingleLetter++;
            plusChar = strchr(plusChar + 1, plusName);
        }

        if (oneChar != NULL) {
            countSingleLetter++;
            oneChar = strchr(oneChar + 1, oneName);
        }

        if (commaChar != NULL) {
            countSingleLetter++;
            commaChar = strchr(commaChar + 1, commaName);
        }

        if (!spaceChar && !plusChar && !oneChar && !commaChar)
            break;
    }

    sizeNameRightPrev = (sizeNameRightPrev+countSingleLetter)/2; // Настоящая длина названия фильма
    // Условие для чётной длины названия
    if (sizeNameRightPrev % 2 == 0)
        sizeNameRightPrev++;

    // Оставшаяся длина на карточке
    int restNameSizePrev = (40-sizeNameRightPrev)/2; //для прописывания пробелов перед\после названия

    // Если фильм длинный, то без пробелов
    if(sizeNameRightPrev == 40) {
        printf("%s", copyName_prev);
    } else {
        // Пробелы перед названием
        for (int i = 1; i < restNameSizePrev; i++)
            printf(" ");

        // Для более ровного вывода
        if (sizeNameRightPrev % 2 == 1 && strlen(pointPrev->a_film.name_of_film) % 2 == 0)
            printf("  ");

        // Для более ровного вывода
        else if (sizeNameRightPrev % 2 == strlen(pointPrev->a_film.name_of_film) % 2)
            printf(" ");

        // Название(предыдущее)
        printf("%s", copyName_prev);

        int flag = 0;
        // Пробелы после названия
        for (int i = 0; i < restNameSizePrev; i++) {
            // Если кол-во символов чётно, то на 1 пробел меньше
            if (strlen(pointPrev->a_film.name_of_film) % 2 == 0 && flag == 0)
                flag = 1;
            else
                printf(" ");
        }
    }

    printf("║    ║");

    // Длина названия фильма (следующий)
    int sizeNameRightNext = strlen(pointNext -> a_film.name_of_film);

    countSingleLetter = 0;
    spaceChar = strchr(pointNext -> a_film.name_of_film, spaceName);
    plusChar = strchr(pointNext -> a_film.name_of_film, plusName);
    oneChar = strchr(pointNext -> a_film.name_of_film, oneName);
    commaChar = strchr(pointNext -> a_film.name_of_film, commaName);

    while (1) {
        if (spaceChar != NULL) {
            countSingleLetter++;
            spaceChar = strchr(spaceChar + 1, spaceName);
        }

        if (plusChar != NULL) {
            countSingleLetter++;
            plusChar = strchr(plusChar + 1, plusName);
        }

        if (oneChar != NULL) {
            countSingleLetter++;
            oneChar = strchr(oneChar + 1, oneName);
        }

        if (commaChar != NULL) {
            countSingleLetter++;
            commaChar = strchr(commaChar + 1, commaName);
        }

        if (!spaceChar && !plusChar && !oneChar && !commaChar)
            break;
    }

    sizeNameRightNext = (sizeNameRightNext+countSingleLetter)/2;

    // TODO: Разобраться с ровным выводом левой и правой карточки
    if (sizeNameRightNext % 2 == 1)
        sizeNameRightNext++;

    int restNameSizeNext = (40 - sizeNameRightNext) / 2;
    if(sizeNameRightNext == 40)
        printf("%s", copyName_next);

    else {
        for (int i = 1; i < restNameSizeNext; i++)
            printf(" ");

        if (sizeNameRightNext % 2 == 1 && strlen(pointNext->a_film.name_of_film) % 2 == 0)
            printf("  ");

        else if (sizeNameRightNext % 2 == strlen(pointNext->a_film.name_of_film) % 2)
            printf(" ");

        // Название(следующее)
        printf("%s", copyName_next);
        int odd = 0;
        for (int i = 0; i < restNameSizeNext; i++){
            if (strlen(pointPrev->a_film.name_of_film) % 2 == 0 && odd == 0)
                odd++;
            else
                printf(" ");
        }
    }

    printf("║\n");
    printf("║                      ╔═══════════════╩════╩═════════════════╗                      ║\n");

    // Длина названия фильма (выбранный)
    int sizeNameRight = strlen(point -> a_film.name_of_film);

    countSingleLetter = 0;
    spaceChar = strchr(point -> a_film.name_of_film, spaceName);
    plusChar = strchr(point -> a_film.name_of_film, plusName);
    oneChar = strchr(point -> a_film.name_of_film, oneName);
    commaChar = strchr(point -> a_film.name_of_film, commaName);

    while (1) {
        if (spaceChar != NULL) {
            countSingleLetter++;
            spaceChar = strchr(spaceChar + 1, spaceName);
        }

        if (plusChar != NULL) {
            countSingleLetter++;
            plusChar = strchr(plusChar + 1, plusName);
        }

        if (oneChar != NULL) {
            countSingleLetter++;
            oneChar = strchr(oneChar + 1, oneName);
        }

        if (commaChar != NULL) {
            countSingleLetter++;
            commaChar = strchr(commaChar + 1, commaName);
        }

        if (!spaceChar && !plusChar && !oneChar && !commaChar)
            break;
    }

    sizeNameRight = (sizeNameRight+countSingleLetter)/2;//длина названия фильма
    printf("╚══════════════════════╣");
    int restNameSize = (40-sizeNameRight)/2;//считаем пробелы перед/после названия
    if(sizeNameRight == 40){
        printf("%s", copyName);
    }
    else {
        for (int i = 1; i < restNameSize; i++) {//пробелы перед названием
            printf(" ");
        }
        if (sizeNameRight % 2 == 1 && strlen(point->a_film.name_of_film) % 2 == 0) {
            printf("  ");
        } else if (sizeNameRight % 2 == strlen(point->a_film.name_of_film) % 2) {
            printf(" ");
        }
        printf("%s", copyName);//печать названия выбранного фильма
        int odd = 0;
        for (int i = 0; i < restNameSize; i++) {//пробелы после названия
            if (strlen(point->a_film.name_of_film) % 2 == 0 && odd == 0) {
                odd++;
            } else {
                printf(" ");
            }
        }
    }

    printf("╠═════════════════════╝\n");
    printf("                       ║");

    //рейтинг в виде звёзд
    char *ratingCurrent = point -> a_film.rating_of_film;
    float Num = atof(ratingCurrent);

    printf("            ");

    for (int i = 1; i <= 10; i++){
        if (Num > i)
            printf("\u2605");
        else if(Num < i)
            printf("\u2606");
    }
    printf("                ");
    printf("║");
    printf("\n                       ╚══════════════════════════════════════╝\n");
    printf("                       \u2B05                                     \u27A1\n"); //стрелки для красоты
}



int main() {
    // Ввызов функции для скрытия курсора
    hidecursor();
    SetConsoleOutputCP(CP_UTF8);
    FILE *open = fopen("C:\\Users\\m_mar\\CLionProjects\\KinoPoisk-on-C\\films.txt", "r");
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

    Print_Film(list_of_films, 0);


    int flagL = 0, flagR = 0, pos;

    while (1) {
        if  (GetKeyState(VK_LEFT) < 0 && flagL == 0) {
            flagL = 1;
//             printf("%s", "Left Key is Pressing\n");
        }
        if (GetKeyState(VK_LEFT) >= 0 && flagL == 1) {
            pos = -1;
            flagL = 0;
            system("cls");

            Print_Film(list_of_films, -1);
        }



        if  (GetKeyState(VK_RIGHT) < 0 && flagR == 0) {
            flagR = 1;
//            printf("%s", "Right Key is Pressing\n");
        }

        if ((GetKeyState(VK_RIGHT) >= 0) && flagR == 1) {
            flagR = 0;
            pos = 1;
            system("cls");
            Print_Film(list_of_films, 1);
        }


    }

    return 0;
}