#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void czy_null(char *tab)
{
    if (tab == NULL)
    {
        exit(EXIT_FAILURE);
    }
}

/* Funkcja "czytaj" czyta wejście do tablicy dwuymiarowej, którą jednocześnie
 * tworzy. Funkcja "czytaj" modyfikuje wskaźnik "tablica wejścia", po
 * zakończeniu działania funkcji wskaźnik "tablica_wejscia" wskazuje na początek
 * tablicy wczytanej za pomocą funkcji "czytaj". */

void czytaj(char **tablica_wejscia, int *wiersze, int *kolumny)
{
    int w = 0; // Zmienne "w" i "k" oznaczają odpowiednio:
    int k = 0; // aktualny wiersz tablicy, aktualną kolumnę tablicy.
    int c;   
    char *tab = (char *)malloc(*wiersze * (*kolumny) * sizeof(char));
    czy_null(tab);
    while((c = getchar()) != EOF)
    {
        switch(w)
        {
            case 0 :
                if (c == '\n')
                {
                    k = 0;
                    w++;
                    (*wiersze)++;
                }
                else
                {
                    (*kolumny)++;
                    tab = realloc(tab, *wiersze * (*kolumny) * sizeof(char));
                    czy_null(tab);
                    *(tab + w * (*kolumny) + k) = c;
                    k++;
                }
                break;
            default :
                if (c == '\n')
                {
                    k = 0;
                    w++;
                    (*wiersze)++;
                }
                else
                {
                    tab = realloc(tab, *wiersze * (*kolumny) * sizeof(char));
                    czy_null(tab);
                    *(tab + w * (*kolumny) + k) = c;
                    k++;
                }
        }
    }
    *tablica_wejscia = tab;
    (*wiersze)--; 
    /* Zmienna "wiersze" po wczytaniu całej tablicy "pokazuje"
     * o jeden więcej wierszy niż ma tablica wejścia, dzieje się
     * tak gdyż zmienna "wiersze" jest przekazywana do funkcji jako
     * argument o wartości 1, należy więc ją (zmienną "wiersze")
     * zmniejszyć o jeden. */
}  


/* Funkcja "czy_pokrycie" sprawdza czy dana kombinacja znaków 
 * jest prawidłowym pokryciem, tablica numerów wierszy 
 * "tab_numerow_wierszy" dostarcza informacji które wiersze uwzględniać
 * przy liczeniu znaków w danej kolumnie. Jeżeli w danej kolumnie 
 * jest jeden znak czyli zmienna "licznik_znakow" wynosi jeden,
 * liczba pokrywających kolumn jest inkrementowana. Jeżeli liczba 
 * pokrywających kolumn jest równa liczbie wszystkich kolumn
 * tablicy wiersza to funkcja zwraca wartość true. */

bool czy_pokrycie(int wiersze, int kolumny, int *tab_numerow_wierszy,
char *tablica_wejscia)
{
    int pokrywajace_kolumny = 0;
    bool czy_sprawdzaj;
    for (int i = 0; i < kolumny; i++)
    {
        int licznik_znakow = 0;
        for (int j = 1; j < wiersze; j++)
        {
            czy_sprawdzaj = false;
            for (int p = 0; p < kolumny; p++) 
            {
                if (*(tab_numerow_wierszy + p) == j)
                    czy_sprawdzaj = true;
            }
            if (czy_sprawdzaj)
            {
                if (*(tablica_wejscia + j * kolumny + i) != '_')
                {
                    licznik_znakow++;
                }
            }
        }
        if (licznik_znakow == 1)
        {
            pokrywajace_kolumny++;
        }
    }
    if (pokrywajace_kolumny == kolumny)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Funkcja "wypisz" wypisuje tablicę wyjścia "tab_wyjscia" z uwzględnieniem 
 * filtra oraz, jeżeli liczba kolumn jest większa niż zero, wypisuje znak 
 * końca wiersza po każdym rozwiązaniu. */

void wypisz(int kolumny, char *tablica_wejscia, char *tab_wyjscia)
{
    for (int j = 0; j < kolumny; j++)
    {
        if (*(tablica_wejscia + j) == '+')
        {
        printf("%c", *(tab_wyjscia + j));
        }
    }
    if (kolumny > 0)
        printf("\n");
}

/* Funkcja "kombinacje" generuje wszystkie kombinacje znaków
 * jakie mogą wystąpić w rozwiązaniu (nie uwzględniając filtra).
 * Każdej kolumnie przypisywany jest jeden znak różny od "_".
 * tworzona jest również tablica numerów wierszy "tab_numerow_wierszy",
 * która zawiera numery wierszów w których są poszczególne znaki danej 
 * kombinacji. W tablicy wyjścia zapisywane są znaki danej kombinacji,
 * następnie jeżeli wynik działania funkcji czy_pokrycie" jest pozytywny, 
 * wypisywana jest tablica wyjścia "tab_wyjscia" z uwzględnieniem filtra. */

void kombinacje(int kolumna, int wiersze, int kolumny, char *tablica_wejscia,
                char *tab_wyjscia, int *tab_numerow_wierszy)
{
    if (kolumna < kolumny)
    {
        for (int i = 1; i < wiersze; i++)
        {
            while (*(tablica_wejscia + i * kolumny + kolumna) == '_')
                i++;
            if (i < wiersze)
            {
            *(tab_wyjscia + kolumna) = *(tablica_wejscia + i * kolumny + kolumna);
            *(tab_numerow_wierszy + kolumna) = i;
            kombinacje(kolumna + 1, wiersze, kolumny, tablica_wejscia, tab_wyjscia,
                       tab_numerow_wierszy);
            }
        }
    }
    else
    {
        if (czy_pokrycie(wiersze, kolumny, tab_numerow_wierszy, tablica_wejscia))
        {
            wypisz(kolumny, tablica_wejscia, tab_wyjscia);
        }
    }
}
    
    
void pokrycie(int wiersze, int kolumny, char *tablica_wejscia)
{
    int kolumna = 0;
    char tab_wyjscia[kolumny];
    int tab_numerow_wierszy[kolumny];
    kombinacje(kolumna, wiersze, kolumny, tablica_wejscia, tab_wyjscia,
               tab_numerow_wierszy);
    free(tablica_wejscia);
}


int main()
{
    char *tablica_wejscia;
    int wiersze = 1; 
    int kolumny = 0;
    czytaj(&tablica_wejscia, &wiersze, &kolumny);
    pokrycie(wiersze, kolumny, tablica_wejscia);
    return 0;
}