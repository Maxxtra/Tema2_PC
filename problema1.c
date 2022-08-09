#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/*
Vom forma cheia. Avem 2 cazuri:
a) daca trebuie sa multiplicam cheia;
b) daca trebuie scurtata cheia.
Pentru a) procedam in felul urmator:
i) multiplicam cheia de nr maxim de ori astfel incat sa nu depaseasca cuvantul;
ii) pentru spatiile ramase luam in ordine litera cu litera de la -> pana cand
se atinge lungimea cuvantului.
Pentru b) procedam in felul urmator:
i) luam litere din cheie pana cand lungimea este cea a cuvantului.

Pentru ambele cazuri folosim un aux care o sa fie cheia initiala, ca mai apoi
sa copiem valoarea din aux in cheie.
*/
void formarecheie(char *cheie, char *cuv)
{
    char aux[13500], b[2];
    int i;
    int dim;
    strcpy(aux, cheie);
    if (strlen(cheie) < strlen(cuv))
    {
        for (i = 1; i < strlen(cuv) / strlen(cheie); i++)
            strcat(aux, cheie);
        dim = strlen(aux);
        if (strlen(cuv) % strlen(aux) != 0)
            for (i = 0; i < strlen(cuv) - dim; i++)
            {
                b[0] = cheie[i];
                b[1] = '\0';
                strcat(aux, b);
            }
    }
    else
    {
        i = 0;
        while (i < strlen(cuv))
        {
            aux[i] = cheie[i];
            i++;
        }
        aux[i] = '\0';
    }
    strcpy(cheie, aux);
}

/*
Verificam daca si cheia si cuvantul dat de la tastatura contin numai litere.
Folosim functia isalpha, care va return 0 daca se gaseste ceva != de o litera,
luand astfel litera cu litera atat cheia, cat si cuvantul.
*/
bool verificare(char *cheie, char *cuv)
{
    int i;
    bool ok1 = true, ok2 = true;
    for (i = 0; i < strlen(cheie); i++)
        if (isalpha(cheie[i]) == 0)
            ok1 = false;
    for (i = 0; i < strlen(cuv) - 1; i++)
        if (isalpha(cuv[i]) == 0)
            ok2 = false;
    if (ok1 == true && ok2 == true)
        return 1;
    return 0;
}

/*
Tinand cont ca avem literele sub forma de a...zZ...a, m-am folosit de
codul ASCII, afland astfel niste formule de prelucrare a codurilor ASCII.
Astfel, am luat doua cazuri: literamica( acesta) si literamare( vezi
urmatoarea functie).
Pentru primul caz, am considerat tranfsormarea
literei mici din cheie. Am calculat distanta de la litera din cheie pana la 
litera a( diferenta intre codul ASCII a literei si codul ASCII a literei a).
Au urmat din nou doua cazuri:
i) transformarea literei mici din cuvant;
    -daca nu depasim codul ASCII al lui z( 122), transformarea se face normal;
    -daca depaseste, folosim formula de calcul astfel incat sa se transforme
    in litera mare;
ii) transformarea literei mari din cuvant;
    -daca nu depasim codul ASCII al lui Z( 90), transformarea se face normal;
    -daca depaseste, folosim formula de calcul astfel incat sa se transforme
    in litera mica;
*/
char literamica(char cheie, char cuv)
{
    int val;
    val = (int)cheie - 97;
    if (islower(cuv) != 0)
    {
        if ((val + (int)cuv) <= 122)
            cuv = (char)(val + (int)cuv);
        else
            cuv = (char)(64 + val + (int)cuv - 122);
    }
    else
    {
        if ((val + (int)cuv) <= 90)
            cuv = (char)(val + (int)cuv);
        else
            cuv = (char)(val + (int)cuv + 6);
    }
    return cuv;
}

/*
Pentru al doilea caz, am considerat tranfsormarea
literei mari din cheie.
Am calculat distanta de la litera din cheie pana la litera a. Au urmat din nou
doua cazuri:
i) transformarea literei mari din cuvant;
    -daca nu depasim codul ASCII al lui Z( 90), transformarea se face normal;
    -daca depaseste, trebuie sa o trnasformam in litera mica;
        a) daca suma( formata din distanta, codul ASCII a literei si 6, cele 6
        caractere care separa literele mari de literele mici in codul ASCII)
        nu depaseste literele mici, atunci o vom face litera mica;
        b) daca depasseste, o vom face litera mare, folosind formula;
ii) transformarea literei mici din cuvant;
    -daca nu depasim codul ASCII al lui z( 122), transformarea se face normal;
    -daca depaseste, folosim formula de calcul astfel incat sa se transforme
    in litera mare;
        a)daca totusi dupa incercarea de transformare in litera mare, codul
        ASCII se afla in intervalul determinat de cele 6 caractere care separa
        literel mari de litere mici, adunam acea diferenta de 6.
*/
char literamare(char cheie, char cuv)
{
    int val;
    val = 25 + (int)cheie - 64;
    if (isupper(cuv) != 0)
    {
        if ((val + (int)cuv) <= 90)
            cuv = (char)(val + (int)cuv);
        else
        {
            if ((6 + val + (int)cuv) <= 122)
                cuv = (char)(6 + val + (int)cuv);
            else
                cuv = (char)(64 + 6 + val + (int)cuv - 122);
        }
    }
    else
    {
        if ((val + (int)cuv) <= 122)
            cuv = (char)(val + (int)cuv);
        else
            cuv = (char)(64 + val + (int)cuv - 122);
        if ((int)cuv >= 91)
            cuv = (char)(6 + (int)cuv);
    }
    return cuv;
}

/*
Citim cheia si cuvantul. 
Daca nu se contin alte caractere in afara de litere:
    -luam litera cu litera din cheie. 
        a) daca este litera mica, vom aplica transformarea literei mici;
        b) daca este litera mare, vom aplica transformarea literei mari.
        c)afisam cuvantul final;
Daca intalnim un caracter care nu este litera, afisam mesajul dorit.
*/
int main()
{
    char cuv[13500], cheie[13500];
    int i;
    scanf("%s %s", cheie, cuv);
    formarecheie(cheie, cuv);
    if (verificare(cheie, cuv) == 1)
    {
        for (i = 0; i < strlen(cheie); i++)
            if (islower(cheie[i]) != 0)
                cuv[i] = literamica(cheie[i], cuv[i]);
            else
                cuv[i] = literamare(cheie[i], cuv[i]);
        printf("%s\n", cuv);
    }
    else
        printf("INVALID\n");
}
