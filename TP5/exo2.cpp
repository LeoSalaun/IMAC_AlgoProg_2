#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>


using std::size_t;
using std::string;


std::vector<string> names(
{
    "Yolo", "Anastasiya", "Clement", "Sirine", "Julien", "Sacha", "Leo", "Margot",
    "JoLeClodo", "Anais", "Jolan", "Marie", "Cindy", "Flavien", "Tanguy", "Audrey",
    "Mr.PeanutButter", "Bojack", "Mugiwara", "Sully", "Solem",
    "Leo", "Nils", "Vincent", "Paul", "Zoe", "Julien", "Matteo",
    "Fanny", "Jeanne", "Elo"
});

unsigned long int hash(string key)
{
    return (unsigned long int) key[0];
}

struct MapNode
{

    string key;
    unsigned long int key_hash;

    int value;

    MapNode* left;
    MapNode* right;

    MapNode(string key, int value)
    {
        this->key = key;
        this->value = value;
        this->key_hash = hash(key);

        this->left = this->right = nullptr;
    }

    /**
     * @brief insertNode insert a new node according to the key hash
     * @param node
     */
    void insertNode(MapNode* node)
    {
        if (this->key_hash > node->key_hash && this->left == nullptr) {
            this->left = node;
        }
        else if (this->key_hash > node->key_hash) {
            this->left->insertNode(node);
        }
        else if (this->key_hash < node->key_hash && this->right == nullptr) {
            this->right = node;
        }
        else if (this->key_hash < node->key_hash) {
            this->right->insertNode(node);
        }
    }

    void insertNode(string key, int value)
    {
        this->insertNode(new MapNode(key, value));
    }

};

struct Map
{
    Map() {
        this->root = nullptr;
    }

    /**
     * @brief insert create a node and insert it to the map
     * @param key
     * @param value
     */
    void insert(string key, int value)
    {
        if (this->root == nullptr) {
            this->root = new MapNode(key,value);
        }
        else {
            this->root->insertNode(key,value);
        }
    }

    /**
     * @brief get return the value of the node corresponding to key
     * @param key
     * @return
     */
    int get(string key)
    {
        MapNode* aux = root;
        unsigned long int keyHash = hash(key);
        while (aux != nullptr) {
            if (aux->key_hash == keyHash) {
                return aux->value;
            }
            else if (aux->key_hash < keyHash) {
                aux = aux->right;
            }
            else {
                aux = aux->left;
            }
        }
        return 0;
    }

    MapNode* root;
};


int main(int argc, char *argv[])
{
    srand(time(NULL));
	Map map;
    std::vector<std::string> inserted;
    
    map.insert("Yolo", 20);
    for (std::string& name : names)
    {
        if (rand() % 3 == 0)
        {
            map.insert(name, rand() % 21);
            inserted.push_back(name);
        }
    }

    printf("map[\"Margot\"]=%d\n", map.get("Margot"));
    printf("map[\"Jolan\"]=%d\n", map.get("Jolan"));
    printf("map[\"Lucas\"]=%d\n", map.get("Lucas"));
    printf("map[\"Clemence\"]=%d\n", map.get("Clemence"));
    printf("map[\"Yolo\"]=%d\n", map.get("Yolo"));
    printf("map[\"Tanguy\"]=%d\n", map.get("Tanguy"));
}
