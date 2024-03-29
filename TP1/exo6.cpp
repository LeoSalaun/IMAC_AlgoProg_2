#include <iostream>

using namespace std;

struct Noeud{
    int donnee;
    Noeud* suivant;
};

struct Liste{
    Noeud* premier;
    // your code
};

struct DynaTableau{
    int* donnees;
    int nb;
    int capacite;
    // your code
};


void initialise(Liste* liste)
{
    liste->premier = nullptr;
}

bool est_vide(const Liste* liste)
{
    return liste->premier == nullptr;
}

void ajoute(Liste* liste, int valeur)
{
    if (liste->premier == nullptr) {
        liste->premier = new Noeud;
        liste->premier->donnee = valeur;
        liste->premier->suivant = nullptr;
    }
    else {
        Noeud * aux = liste->premier;
        while (aux->suivant != nullptr) {
            aux = aux->suivant;
        }
        aux->suivant = new Noeud;
        aux->suivant->donnee = valeur;
        aux->suivant->suivant = nullptr;
    }
}

void affiche(const Liste* liste)
{
    Noeud * aux = liste->premier;
    while (aux != nullptr) {
        cout << "-- " << aux->donnee << " --" << endl;
        aux = aux->suivant;
    }
}

int recupere(const Liste* liste, int n)
{
    Noeud * aux = liste->premier;
    int i=0;
    while (aux != nullptr && i < n) {
        aux = aux->suivant;
        i++;
    }
    if (i < n) {
        return -1;
    }
    else {
        return aux->donnee;
    }
}

int cherche(const Liste* liste, int valeur)
{
    if (liste->premier->donnee == valeur) {
        return 0;
    }
    Noeud * aux = liste->premier;
    bool trouve = (aux->donnee == valeur);
    int i=0;
    while (aux->suivant != nullptr && !(trouve)) {
        aux = aux->suivant;
        i++;
        bool trouve = (aux->donnee == valeur);
        //cout << aux->donnee << " " << valeur << " " << (aux->suivant != nullptr && !(trouve)) << endl;
    }
    if (trouve) {
        return i;
    }
    else {
        return -1;
    }
}

void stocke(Liste* liste, int n, int valeur)
{
    Noeud * aux = liste->premier;
    int i=0;
    while (aux->suivant != nullptr && i < n) {
        aux = aux->suivant;
        i++;
    }
    if (i == n) {
        aux->donnee = valeur;
    }
}


void initialise(DynaTableau* tableau, int capacite)
{
    tableau->capacite = capacite;
    tableau->donnees = (int*) malloc(capacite*sizeof(int));
    tableau->nb = 0;
}

void ajoute(DynaTableau* tableau, int valeur)
{
    if (tableau->nb == tableau->capacite) {
        /*DynaTableau * tabTemp;
        initialise(tabTemp,tableau->capacite+1);
        for (int i=0 ; i<tableau->capacite ; i++) {
            tabTemp->donnees[i] = tableau->donnees[i];
        }
        //free(tableau);
        tableau = tabTemp;*/
    }
    tableau->donnees[tableau->nb] = valeur;
    tableau->nb++;
}

bool est_vide(const DynaTableau* liste)
{
    return liste->nb == 0;
}

void affiche(const DynaTableau* tableau)
{
    for (int i=0 ; i<tableau->nb ; i++) {
        cout << "[[ " << tableau->donnees[i] << " ]]" << endl;
    }
}

int recupere(const DynaTableau* tableau, int n)
{
    if (n > tableau->nb) {
        return -1;
    }
    else {
        return tableau->donnees[n];
    }
}

int cherche(const DynaTableau* tableau, int valeur)
{
    int i=0;
    bool trouve = tableau->donnees[i] == valeur;
    while (i<tableau->nb && !(trouve)) {
        i++;
        trouve = tableau->donnees[i] == valeur;
    }
    if (trouve) {
        return i;
    }
    else {
        return -1;
    }
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    if (n <= tableau->nb) {
        tableau->donnees[n-1] = valeur;
    }
}

void pousse_file(DynaTableau* liste, int valeur)
//void pousse_file(Liste* liste, int valeur)
{
    ajoute(liste,valeur);
}

int retire_file(DynaTableau* liste)
//int retire_file(Liste* liste)
{
    // int res = liste->premier->donnee;
    // liste->premier = liste->premier->suivant;
    // return res;

    if (liste->nb == 0) {
        return -1;
    }
    int res = liste->donnees[0];
    liste->nb--;
    for (int i=0 ; i<liste->nb ; i++) {
        liste->donnees[i] = liste->donnees[i+1];
    }
    return res;
}

void pousse_pile(DynaTableau* liste, int valeur)
//void pousse_pile(Liste* liste, int valeur)
{
    ajoute(liste,valeur);
}

int retire_pile(DynaTableau* liste)
//int retire_pile(Liste* liste)
{
    // if (liste->premier == nullptr) {
    //     return -1;
    // }
    // else if (liste->premier->suivant == nullptr) {
    //     int res = liste->premier->donnee;
    //     delete liste->premier;
    //     liste->premier = nullptr;
    //     return res;
    // }
    // else if (liste->premier->suivant->suivant == nullptr) {
    //     int res = liste->premier->suivant->donnee;
    //     delete liste->premier->suivant;
    //     liste->premier->suivant = nullptr;
    //     return res;
    // }
    // int res;
    // Noeud * auxFollow = liste->premier;
    // Noeud * aux = liste->premier->suivant;
    // while (aux->suivant != nullptr) {
    //     aux = aux->suivant;
    //     auxFollow = auxFollow->suivant;
    // }
    // res = aux->donnee;
    // delete aux;
    // auxFollow->suivant = nullptr;
    // return res;

    if (liste->nb == 0) {
        return -1;
    }
    liste->nb--;
    return liste->donnees[liste->nb];
}


int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste à " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste à " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    // Liste pile;
    // Liste file;

    DynaTableau pile;
    DynaTableau file;
    // initialise(&pile);
    // initialise(&file);
    initialise(&pile,7);
    initialise(&file,7);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
