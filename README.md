# Tema2_PC

 Cerinta I - Criptare Parole : Cifrul Vigenere modificat
 
    1) implementare
        - succesiunea de litere nu este cea data de codul ASCII: A...Za...z;
        - plecand insa pe aceasta idee, am incercat sa o
    scot la capat.
    2) formule
        - am scos formule de calcul, astfel incat sa pot transforma
        literele mari in litere mici si viceversa;
        - nu imi dadeam seama cum sa scot diferenta de acele 6 caractere,
        insa daca adunam 6 era suficient.
    Problema decurge in felul urmator:
    a) citim cheia si cuvantul. 
    - daca nu se contin alte caractere in afara de litere:
    b) luam litera cu litera din cheie. 
            - daca este litera mica, vom aplica transformarea literei mici;
            - daca este litera mare, vom aplica transformarea literei mari.
    c) afisam cuvantul final;
    - daca intalnim un caracter care nu este litera, afisam mesajul dorit.
    Transformarile sunt doar formule de calcul cu ajuorul codului ASCII.
    

Cerinta II - Automatically fill

    1) inlocuirea camp-ului cu valoarea data;
        - problemele au inceput sa apara in momentul in care eu faceam o
        singura inlocuire, chiar daca probabil mai erau spatii de inlocuit;
        - dupa ce am rezolvat aceasta problema, am incercat sa-mi dau seama
        cum sa verific daca in stanga si dreapta am ceva diferit de cifre
        si litere, numindu-le astfel "caractere speciale";
    2) alocarea dinamica:
        - a durat cateva ore pana am reusit sa-mi dau seama cum sa aloc memorie
        atat pentru structura, cat si pentru fraza;
        - problema la alocarea dinamica a frazei a aparut in momentul in care
        am incercat sa aloc exact atata memorie de care aveam nevoie;
    Problema decurge in felul urmator:
    a) apeleam structura;
    b) alocam dinamic fraza; 
    c) citim in structura lista fraza si ce trebuie inlocuit
    si cu ce se va inlocuit;
    d) aplicam functia de inlocuire in fraza;
    e) afisam fraza. 
    

 Cerinta III - Generare Parole
 
    1) efectuarea codificarilor
        - codificarea 1 a fost destul de dificila, deoarece nu am intuit din
        prima cum sa aloc din prima memorie;
        - codificarea 2 a necesitat consultarea materialelor teoretice,
        deoarece operatiile pe biti sunt dificile, in special;
        - codificarea 3 a fost cea mai usoara, deoarece a necesitat doar o
        functie din biblioteca.
    2) afisarea
        - am abordat metoda de a afisa direct pe ecran, pentru a nu mai
        complica realocarea dinamica;
    Problema decurge in felul urmator:
    a) citim cele doua date de la tastatura;
    b) alocam dinamic sirul cu exact atatea elemente cate ne indica lungimea;
    c) generam seed-ul random;
    d) apelam functia de afisare unde se vor face operatiile aferente,
    e) se face afisarea direct pe ecran. 
