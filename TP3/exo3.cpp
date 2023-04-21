// #include "mainwindow.h"
// #include "tp3.h"
// #include <QApplication>
// #include <time.h>
// #include <stack>
// #include <queue>

// MainWindow* w = nullptr;
// using std::size_t;

#include <time.h>       /* time */
#include <iostream>
using namespace std;

int max(int n1, int n2) {
    if (n1 > n2) {
        return n1;
    }
    else {
        return n2;
    }
}

struct SearchTreeNode
{    
    SearchTreeNode* left;
    SearchTreeNode* right;
    int value;

    void initNode(int value)
    {
        // init initial node without children
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

	void insertNumber(int value) {
        // create a new node and insert it in right or left child
        if (value >= this->value) {
            if (this->right == nullptr) {
                this->right = new SearchTreeNode(value);
            }
            else {
                this->right->insertNumber(value);
            }
        }
        else {
            if (this->left == nullptr) {
                this->left = new SearchTreeNode(value);
            }
            else {
                this->left->insertNumber(value);
            }
        }
    }

	int height() {
        // should return the maximum height between left child and
        // right child +1 for itself. If there is no child, return
        // just 1

        int heightRight = 0, heightLeft = 0;
        if (this->right != nullptr) {
            heightRight = this->right->height();
        }
        if (this->left != nullptr) {
            heightLeft = this->left->height();
        }

        return 1 + max(heightRight,heightLeft);  // MAX À DÉFINIR
    }

	int nodesCount() {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1

        int countRight = 0, countLeft = 0;
        if (this->right != nullptr) {
            countRight = this->right->nodesCount();
        }
        if (this->left != nullptr) {
            countLeft = this->left->nodesCount();
        }

        return 1 + countRight + countLeft;
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        return this->right == nullptr && this->left == nullptr;
	}

	void allLeaves(SearchTreeNode* leaves[], int* leavesCount) {
        // fill leaves array with all leaves of this tree
        if (this->right == nullptr && this->left == nullptr) {
            leaves[*leavesCount] = this;
            (*leavesCount)++;
        }
        else {
            if (this->left != nullptr) {
                this->left->allLeaves(leaves,leavesCount);
            }
            if (this->right != nullptr) {
                this->right->allLeaves(leaves,leavesCount);
            }
        }
	}

	void inorderTravel(SearchTreeNode* nodes[], int* nodesCount) {
        // fill nodes array with all nodes with inorder travel
        if (this->left != nullptr) {
            this->left->inorderTravel(nodes,nodesCount);
        }
        nodes[*nodesCount] = this;
        (*nodesCount)++;
        if (this->right != nullptr) {
            this->right->inorderTravel(nodes,nodesCount);
        }
	}

	void preorderTravel(SearchTreeNode* nodes[], int* nodesCount) {
        // fill nodes array with all nodes with preorder travel
        nodes[*nodesCount] = this;
        (*nodesCount)++;
        if (this->left != nullptr) {
            this->left->preorderTravel(nodes,nodesCount);
        }
        if (this->right != nullptr) {
            this->right->preorderTravel(nodes,nodesCount);
        }
	}

	void postorderTravel(SearchTreeNode* nodes[], int* nodesCount) {
        // fill nodes array with all nodes with postorder travel
        if (this->left != nullptr) {
            this->left->postorderTravel(nodes,nodesCount);
        }
        if (this->right != nullptr) {
            this->right->postorderTravel(nodes,nodesCount);
        }
        nodes[*nodesCount] = this;
        (*nodesCount)++;
	}

	SearchTreeNode* find(int value) {
        // find the node containing value

        if (this->value == value) {
            return this;
        }
        else if (this->value <= value && this->right != nullptr) {
            return this->right->find(value);
        }
        else if (this->value > value && this->left != nullptr) {
            return this->left->find(value);
        }
        else {
            return nullptr;
        }
	}

    void reset()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
        left = right = nullptr;
    }

    void print(int nbTab) {
        if (nbTab == 0) {
            cout << "+--------------------------------------+" << endl << "root : ";
        }
        cout << this->value << endl;
        if (this->left != nullptr) {
            for (int i=0 ; i<nbTab+1 ; i++) {
                cout << "   ";
            }
            cout << "left :  ";
            this->left->print(nbTab+1);
        }
        if (this->right != nullptr) {
            for (int i=0 ; i<nbTab+1 ; i++) {
                cout << "   ";
            }
            cout << "right : ";
            this->right->print(nbTab+1);
        }
    }

    SearchTreeNode(int value) {initNode(value);}
    ~SearchTreeNode() {}
    int get_value() const {return value;}
    SearchTreeNode* get_left_child() const {return left;}
    SearchTreeNode* get_right_child() const {return right;}
};

SearchTreeNode* createNode(int value) {
    return new SearchTreeNode(value);
}



void printArray(SearchTreeNode * array[],int size) {
    cout << "- ";
    for (int i=0; i<size; i++)
    {
        cout << array[i]->value << " - ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
	// QApplication a(argc, argv);
	// MainWindow::instruction_duration = 200;
    // w = new BinarySearchTreeWindow<SearchTreeNode>();
	// w->show();

	// return a.exec();

    srand(time(NULL));

    SearchTreeNode *stn = new SearchTreeNode(rand()%20);

    cout << "init ok" << endl;

    for (int i=0 ; i<9 ; i++) {
        stn->insertNumber(rand()%20);
    }

    cout << "insert ok" << endl;

    stn->print(0);

    cout << endl << "Height : " << stn->height() << endl;

    cout << endl << "Nodes : " << stn->nodesCount() << endl << endl;

    SearchTreeNode* array[10];

    int count = 0;
    stn->allLeaves(array,&count);

    printArray(array,count);

    count = 0;
    stn->inorderTravel(array,&count);
    printArray(array,count);

    count = 0;
    stn->preorderTravel(array,&count);
    printArray(array,count);

    count = 0;
    stn->postorderTravel(array,&count);
    printArray(array,count);

    int toFind = rand()%20;
    SearchTreeNode * find = stn->find(toFind);
    cout << "to find : " << toFind << endl;
    if (find == nullptr) {
        cout << "non trouvé" << endl;
    }
    else {
        cout << "trouvé" << endl;
    }
}
