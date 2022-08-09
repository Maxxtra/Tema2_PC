#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Declaram structura din enunt.
*/
struct pereche
{
    char *camp, *valoare;
};

/*
Facem functie pentru citire. Totodata, alocam dinamic structura si fraza,
pe care le vom citi de la tastatura.
Am citit linie cu linie. Atfel, am citit o data n ori si mai apoi o utlima
linie, unde se afla fraza. Am separat cele doua cuvinte de pe o linie, ca mai
apoi sa le pun in structura, pe pozitii succesive. La final, am citit fraza. 
Fiind o funtie de tip struct, am returnat lista, compusa din cuvantul care
trebuie inlocuit si cel care urmeaza sa fie pus.
Alocarile dinamice, s-au facut in fucntie de spatiul pe care trebuia sa
il aloc. Nu am suprascris nimic, de aceea nu am folosit realloc.
*/
struct pereche *citeste(char *fraza, int *n)
{
    struct pereche *lista = NULL;
    char linie[15000];
    char *camp, *valoare;
    fgets(linie, 6, stdin);
    *n = atoi(linie);
    lista = (struct pereche *)malloc(*n * sizeof(struct pereche));
    for (int i = 0; i < *n; i++)
    {
        fgets(linie, 200, stdin);
        linie[strlen(linie) - 1] = '\0';
        char *ptr = strtok(linie, " ");
        camp = (char *)malloc((strlen(ptr) + 1) * sizeof(char));
        strcpy(camp, ptr);
        lista[i].camp = camp;
        ptr = strtok(NULL, " ");
        valoare = (char *)malloc((strlen(ptr) + 1) * sizeof(char));
        strcpy(valoare, ptr);
        lista[i].valoare = valoare;
    }
    fgets(linie, 15000, stdin);
    strcpy(fraza, linie);
    return lista;
}

/*
Facem fucntie care sa inlocuiasca in fraza citita toate aparitiile ale camp-ului
cu valoarea aferenta lui. De aceea, parcurgem toate camp-urile, astfel vom
cauta in fraza toate aparitiile ale acestuia, ca mai apoi sa verificam daca
avem in stanga si dreapta avem caractere care sunt diferite de cifre sau litere.
Daca sunt, inlocuim clasic camp-ul cu valoarea.
*/
void inlocuire(struct pereche *lista, char *fraza, int *n)
{
    char *poz, aux[20000];
    int index = 0, i;
    int lungime;
    for (i = 0; i < *n; i++)
    {
        lungime = strlen(lista[i].camp);
        poz = strstr(fraza, lista[i].camp);
        while (poz)
        {
            if (!isalnum(*(poz - 1)) && !isalnum(*(poz + lungime)))
            {
                index = poz - fraza;
                strcpy(aux, fraza);
                fraza[index] = '\0';
                strcat(fraza, lista[i].valoare);
                strcat(fraza, aux + index + lungime);
            }
            poz = strstr(poz + 1, lista[i].camp);
        }
    }
}

/*
Apeleam structura. Alocam dinamic fraza, initial cu o valoare extrem de mare,
dar care totusi sa nu fie exagerat de mare, ca sa nu ramana memorie alocata
degeaba. Apoi, citim in structura lista fraza noastra si ce trebuie inlocuit
si cu ce se va inlocuit. Aplicam functia de inlocuire in fraza. Afisam fraza
dupa editarile efectuate.
*/
int main()
{
    struct pereche *lista = NULL;
    char *fraza = NULL;
    int n = 0;
    fraza = (char *)malloc(20000 * sizeof(char));
    lista = citeste(fraza, &n);
    inlocuire(lista, fraza, &n);
    printf("%s", fraza);
    free(fraza);
    free(lista);
    return 0;
}
