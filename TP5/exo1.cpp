#include <time.h>
#include <vector>
#include <string>
#include <iostream>

struct Element
{
    std::string value;
    Element * next;

    Element(std::string value) {
        this->value = value;
        this->next = nullptr;
    }
};


std::vector<std::string> names(
{
    "Yolo", "Anastasiya", "Clement", "Sirine", "Julien", "Sacha", "Leo", "Margot",
    "JoLeClodo", "Anais", "Jolan", "Marie", "Cindy", "Flavien", "Tanguy", "Audrey",
    "Mr.PeanutButter", "Bojack", "Mugiwara", "Sully", "Solem",
    "Leo", "Nils", "Vincent", "Paul", "Zoe", "Julien", "Matteo",
    "Fanny", "Jeanne", "Elo"
});

int hash(std::vector<Element*> hash_table, std::string element)
{
    return (int) element[0] % hash_table.size();
}

void insert(std::vector<Element*>* hash_table, std::string element)
{
    // use (*this)[i] or this->get(i) to get a value at index i
    if ((*hash_table)[hash(*hash_table, element)] == nullptr) {
        (*hash_table)[hash(*hash_table, element)] = new Element(element);
    }
    else {
        
        Element* aux = (*hash_table)[hash(*hash_table, element)];
        
        while (aux->next != nullptr) {
            aux = aux->next;
        }
        aux->next = new Element(element);
        aux->next->value = element;
    }
}

/**
 * @brief buildHashTable: fill the HashTable with given names
 * @param table table to fill
 * @param names array of names to insert
 * @param namesCount size of names array
 */
void buildHashTable(std::vector<Element*> hash_table, std::string* names, int namesCount)
{
    for (int i=0 ; i<31 ; i++) {
        insert(&hash_table,names[i]);
    }
}

bool contains(std::vector<Element*> hash_table, std::string element)
{
    if (hash_table[hash(hash_table, element)] == nullptr) {
        return false;
    }
    Element* aux = hash_table[hash(hash_table, element)];
    
    while (aux->next != nullptr && aux->value != element) {
        aux = aux->next;
    }
    return aux->value == element;
}

void printTable(Element * element) {
    Element * aux = element;
    while (aux != nullptr) {
        std::cout << aux->value << " ; ";
        aux = aux->next;
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    std::vector<Element*> table;
    table.resize(10);

    for (int i=0 ; i<10 ; i++) {
        table[i] = nullptr;
    }

    for (int i=0 ; i<31 ; i++) {
        insert(&table,names[i]);
    }

    std::cout << contains(table,"Leo") << std::endl << contains(table,"Lea") << std::endl;

    for (int i=0 ; i<10 ; i++) {
        printTable(table[i]);
    }
}
