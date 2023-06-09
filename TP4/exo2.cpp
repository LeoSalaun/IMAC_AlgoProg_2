#include "HuffmanNode.h"

using std::size_t;
using std::string;

#include <vector>

#include <iostream>

void exchange(std::vector<HuffmanNode*> array, int i, int j);
void processCharFrequences(string data, std::vector<int>& frequences);
void buildHuffmanHeap(const std::vector<int>& frequences, std::vector<HuffmanNode*>& priorityMinHeap, int& heapSize);
HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode);
HuffmanNode* buildHuffmanTree(std::vector<HuffmanNode*>& priorityMinHeap, int heapSize);
void insertHeapNode(std::vector<HuffmanNode*> &heap, int &heapSize, HuffmanNode* newNode);
string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree);
string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot);


void main_function(HuffmanNode*& huffmanTree)
{
    string data = "Wesh, bien ou quoi ? t'habites dans le coin ou quoi ? J't'ai vue passer dans l'allée, ton boule me rend romantique, pièce";

    // this array store each caracter frequences indexed by their ascii code
    std::vector<int> characterFrequences;
    for (int i = 0 ; i < 128 ; i++){
        characterFrequences.push_back(0);
    }

    // this array store each caracter code indexed by their ascii code
    string characterCodes[128];
    std::vector<HuffmanNode*> priorityMinHeap;
    int heapSize = 0;

    processCharFrequences(data, characterFrequences);
    // afficher characterFrequences

    std::cout << "processCharFrequences :" << std::endl;
    for (int i=0 ; i<128 ; i++) {
        std::cout << char(i) << " -> " << characterFrequences[i] << " | ";
    }
    std::cout << std::endl << std::endl;

    buildHuffmanHeap(characterFrequences, priorityMinHeap, heapSize);
    
    // afficher le heap

    std::cout << "buildHuffmanHeap :" << std::endl;
    for (int i=0 ; i<heapSize ; i++) {
        std::cout << i << " -> " << priorityMinHeap[i]->character << "-" << priorityMinHeap[i]->frequences << " | ";
    }
    std::cout << std::endl << std::endl;

    huffmanTree = buildHuffmanTree(priorityMinHeap, heapSize);
    huffmanTree->processCodes("");
    //std::cout << heapSize << std::endl;

    HuffmanNode* tmp = huffmanTree;
    std::cout << huffmanTree->right->left->character << std::endl;
    std::cout << "yo" << std::endl;

    while (tmp->character == '\0') {
        tmp = tmp->right;
    }
    std::cout << tmp->character << std::endl;

    string encoded = huffmanEncode(data, huffmanTree);
    //string decoded = huffmanDecode(encoded, *huffmanTree);

    printf("Encoded: %s\n", encoded.c_str());
    //printf("Decoded: %s\n", decoded.c_str());
}


void exchange(std::vector<HuffmanNode*> array, int i, int j) {
    HuffmanNode* temp = array[j];
    array[j] = array[i];
    array[i] = temp;
}


void processCharFrequences(string data, std::vector<int>& frequences)
{
    /**
      * Fill `frequences` array with each caracter frequence.
      * frequences is an array of 256 int. frequences[i]
      * is the frequence of the caracter with ASCII code i
     **/

    // Your code

    for (char character : data) {
        frequences[character]++;
    }
    
}

void insertHeapNode(std::vector<HuffmanNode*> &heap, int &heapSize, HuffmanNode* newNode)
{
    /**
      * Insert a HuffmanNode into the lower heap. A min-heap put the lowest value
      * as the first cell, so check the parent should be lower than children.
      * Instead of storing int, the cells of std::vector<HuffmanNode*> store HuffmanNode*.
      * To compare these nodes use their frequences.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/

    // Your code
    int i = heapSize;
    if (heap.size() == heapSize) {
        heap.push_back(newNode);
    }
	else {
        heap[heapSize] = newNode;
    }
    
	while (i>0 && heap[i]->frequences < heap[(i-1)/2]->frequences) {
		exchange(heap,i,(i-1)/2);
		i = (i-1)/2;
	}

    heapSize++;
}

void buildHuffmanHeap(const std::vector<int>& frequences, std::vector<HuffmanNode*>& priorityMinHeap, int& heapSize)
{
    /**
      * Do like Heap::buildHeap. Use only non-null frequences
      * Define heapSize as numbers of inserted nodes
      * allocate a HuffmanNode with `new`
     **/

    // Your code
    heapSize = 0;
    for (int i=0 ; i<frequences.size() ; i++) {
        if (frequences[i] != 0) {
            insertHeapNode(priorityMinHeap,heapSize,new HuffmanNode(char(i),frequences[i]));
        }
	}

}

void heapify(std::vector<HuffmanNode*> HuffmanNode, int heapSize, int nodeIndex)
{
    /**
      * Repair the heap starting from nodeIndex. this is a min-heap,
      * so check the parent should be lower than children.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/
    // Your code

    int i_min = nodeIndex;
	for (int i=nodeIndex ; i<2*nodeIndex+1 && i<heapSize ; i++) {
		if (HuffmanNode[i]->frequences < HuffmanNode[i_min]->frequences) {
			i_min = i;
		}
	}

	if (i_min != nodeIndex) {
		exchange(HuffmanNode,nodeIndex,i_min);
		heapify(HuffmanNode,heapSize,i_min);
	}
}


HuffmanNode* extractMinNode(std::vector<HuffmanNode*> &HuffNode, int &heapSize)
{
    /**
      * Extract the first cell, replace the first cell with the last one and
      * heapify the heap to get a new well-formed heap without the returned cell
      * you can use `this->swap`
     **/

    // Your code

    HuffmanNode *res = HuffNode[0];
    exchange(HuffNode,0,heapSize-1);
    heapify(HuffNode,heapSize-1,0);
    //std::cout << HuffNode[0]->character << "-" << res->character << std::endl;
    //heapSize--;

    return res;
}

HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode)
{
    /**
     * Make a subtree (parent + 2 children) with the given 2 nodes.
     * These 2 characters will be the children of a new parent node which character is '\0'
     * and frequence is the sum of the 2 children frequences
     * Return the new HuffmanNode* parent
     **/
    // Your code
    HuffmanNode* parent = new HuffmanNode();
    parent->left = leftNode;
    parent->right = rightNode;
    parent->frequences = leftNode->frequences + rightNode->frequences;
    
    return parent;
}

HuffmanNode* buildHuffmanTree(std::vector<HuffmanNode*>& priorityMinHeap, int heapSize)
{
    /**
      * Build Huffman Tree from the priorityMinHeap, pick nodes from the heap until having
      * one node in the heap. For every 2 min nodes, create a subtree and put the new parent
      * into the heap. The last node of the heap is the HuffmanTree;
      * use extractMinNode()
     **/

    // Your code

    HuffmanNode* leftNode;
    HuffmanNode* rightNode;
    HuffmanNode* subtree;

    while (heapSize > 1) {
        //std::cout << heapSize << std::endl;
        leftNode = extractMinNode(priorityMinHeap,heapSize);
        heapSize--;
        rightNode = extractMinNode(priorityMinHeap,heapSize);
        heapSize--;
        subtree = makeHuffmanSubTree(rightNode,leftNode);
        insertHeapNode(priorityMinHeap,heapSize,subtree);
        heapSize++;
        //std::cout << heapSize << std::endl;
        //heapSize--;
        //std::cout << heapSize << std::endl;
        //std::cout << leftNode->character << " - " << subtree->left->character << std::endl;
    }
    //std::cout << heapSize << std::endl;

    return priorityMinHeap[0];
}

void HuffmanNode::processCodes(const std::string& baseCode)
{
    /**
      * Travel whole tree of HuffmanNode to determine the code of each
      * leaf/character.
      * Each time you call the left child, add '0' to the baseCode
      * and each time call the right child, add '1'.
      * If the node is a leaf, it takes the baseCode.
     **/

    // Your code

    this->code = baseCode;
    if (this->right) {
        this->right->processCodes(baseCode+'1');
    }
    if (this->left) {
        this->left->processCodes(baseCode+'0');
    }
}

void HuffmanNode::fillCharactersArray(std::string charactersCodes[])
{
    /**
      * Fill the string array with all nodes codes of the tree
      * It store a node into the cell corresponding to its ascii code
      * For example: the node describing 'O' should be at index 79
     **/
    if (!(this->left) && !(this->right))
        charactersCodes[this->character] = this->code;
    else {
        if (this->left)
            this->left->fillCharactersArray(charactersCodes);
        if (this->right)
            this->right->fillCharactersArray(charactersCodes);
    }
}

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree)
{
    /**
      * Encode a string by using the huffman compression.
      * With the huffmanTree, determine the code for each character
     **/

    // Your code
    std::string charactersCodes[128]; // array of 256 huffman codes for each character
    huffmanTree->fillCharactersArray(charactersCodes);
    string encoded = "";
    for (char character : toEncode) {
        encoded += charactersCodes[character];
    }

    return encoded;
}


string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot)
{
    /**
      * Use each caracters of toDecode, which is '0' either '1',
      * to travel the Huffman tree. Each time you get a leaf, get
      * the decoded character of this node.
     **/
    // Your code

    string decoded = "";

    HuffmanNode current = huffmanTreeRoot;

    for (int i=0 ; i<toDecode.length() ; i++) {
        switch (toDecode[i])
        {
        case '0':
            current = *(current.left);
            break;
        
        case '1':
            current = *(current.right);
            break;
        default :
            if (!(current.left) && !(current.right)) {
                decoded += current.character;
                current = huffmanTreeRoot;
            }
        }
    }

    return decoded;
}


int main(int argc, char *argv[])
{
    HuffmanNode* root; 
    main_function(root);
}
