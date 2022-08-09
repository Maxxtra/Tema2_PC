#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
Facem functie pentru generarea sirului.
Am foloit functia predefinita rand() alaturi de 94(125-32+1) reprezentand
numarul de caractere maxim cu care se va lucra si 32, reprezentand
codul de referinta de la care se va incepe generarea.
*/
void generare(char *sir, int *lungime)
{
    int i;
    for (i = 0; i < *lungime; i++)
        sir[i] = rand() % 94 + 32;
    sir[*lungime] = '\0';
}
/*
Facem functie pentru codificarea 1.
Alocam dinamic vectorul v, cel pe care il vom returna, si aux, cel de care ne
vom folosi pentru a completa corect vecotrul v, deoarece in aux vom pune
oglinditul numaruli de aparitii, pentru numeerele cu mai mult de o cifra.
Alocam static un vector static de aparitii, care o sa aiba 126 de elemente( valoarea
ultimului character +1) si o sa fie plin de 0-uri initial. 
Pe prima pozitie a vectorului v vom pune caracterul trimis. Pe pozitia sa din
vectorul de aparitii vom mari cu o unitate numarul aparitiilor. Daca numarul de
aparitii este <=9 o sa-l punem uzual in vector.
Daca in schimb are cel putin 2 cifre, luam litera cu litera, cream ogliniditul
sau ca mai apoi sa punem in ordinea corecta in vectorul v.
Exemplu:
nr apar=14
aux[0]=4 si aux[1]=1
v[1]=1 si v[2]= 4
*/
char *codificare1(char a)
{
    static int apar[126] = {0};
    char *v, *aux;
    int poz, i = 1, j, copie;
    v = (char *)calloc(3, sizeof(char));
    aux = (char *)malloc(3 * sizeof(char));
    poz = (int)a;
    v[0] = a;
    if (apar[poz] < 10)
        v[1] = apar[poz] + '0';
    else
    {
        copie = apar[poz];
        while (copie != 0)
        {
            aux[i] = copie % 10 + '0';
            copie /= 10;
            aux = (char *)realloc(aux, 3 + i);
            v = (char *)realloc(v, 3 + i);
            i++;
        }
        for (j = 1; j < i; j++)
            v[j] = aux[i - j];
    }
    v[i + 1] = '\0';
    apar[poz]++;
    free(aux);
    return v;
}

/*
Facem functie pentru codificarea 2.
Alocam dinamic vectorul v, cel pe care il vom returna. Returnand doar 2 caractere,
ii vom da maxim 3( 1 pentru '\0').
Pentru inceput, am facut operatia de xor intre codul ascii al caracterului
nostru cu 72( deoarece 72= 001001000 care se va afla prin 2*2*2*2*2*2+2*2*2)
pentru a inversa bitii 3 si 6. Mai apoi, in urma breviarului teoretic de la
laborator, am invatat cum sa numar bitii cu valoarea 1. Am mers pana la 32,
deoarece avem 8 biti*4. Ulterior, am facut oreparia de or cu masca( fiind 
00100000 se va calcula 2*2*2*2*2). La final, am setat la 0 LSB-ul si
am transformat in caracter codul binar.
Astfel, vectorul nostru o sa aiba pe pozitia 0 codul pe care l-am obtinut
in urma operatiilor mai sus explicate, iar pe pozitia 1 numarul cerut in
ipoteza. 

*/
char *codificare2(char a)
{
    int nr = 0, i;
    char cod, *v;
    v = (char *)calloc(3, sizeof(char));
    cod = a ^ 72;
    for (i = 0; i < 32; i++)
        if ((1 << i) & cod)
            nr++;
    cod = cod | 32;
    cod = cod & 254;
    v[0] = cod;
    v[1] = nr + '0';
    v[2] = '\0';
    return v;
}

/*
Facem functie pentru codificarea 2.
Alocam dinamic vectorul v, cel pe care il vom returna. Returnand doar 1 caracter,
ii vom da maxim 2( 1 pentru '\0').
Folosind functia toupper, care returneaza majuscula unei litere mici, ignorand
astfel daca se da peste o litera mare sau un caracter.
*/
char *codificare3(char a)
{
    char *v;
    v = (char *)calloc(2, sizeof(char));
    v[0] = toupper(a);
    v[1] = '\0';
    return v;
}

/*
Facem functie pentru afisare. Am parcurs lungimea, iar pentru feicare, am generat
acel numar random care va da tipul codificarii. Am apelat functiile aferente
codificarilor, iar dupa fiecare operatie am afisat direct, fara sa mai fie
nevoie sa aloc memorie din nou. Returnand la fiecare fucntie un sir,
am creat un pointer. 
*/
void afisare(char *sir, int *lungime, char *(*ofera[3])(char))
{
    int i;
    int val;
    for (i = 0; i < *lungime; i++)
    {
        val = rand() % 3;
        if (val == 0)
        {
            char *str = ofera[0](sir[i]);
            printf("%s", str);
            free(str);
        }
        if (val == 1)
        {
            char *str = ofera[1](sir[i]);
            printf("%s", str);
            free(str);
        }
        if (val == 2)
        {
            char *str = ofera[2](sir[i]);
            printf("%s", str);
            free(str);
        }
    }
    printf("\n");
}

/*
Citim cele doua date de la tastatura. Alocam dinamic sirul cu exact atatea
elemente cate ne indica lungimea citita de la tastatura. Generam seed-ul
random. Apelam functia de afisare unde se vor face operatiile aferente,
iar mai apoi se va afisa direct.
*/
int main()
{
    int seed, lungime;
    char *sir;
    scanf("%d %d", &seed, &lungime);
    sir = (char *)malloc((lungime + 1) * sizeof(char));
    srand(seed);
    generare(sir, &lungime);
    char *(*ofera[3])(char) = {codificare1, codificare2, codificare3};
    afisare(sir, &lungime, ofera);
    free(sir);
    return 0;
}
