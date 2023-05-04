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

    SearchTreeNode * rightRotate() {
        SearchTreeNode * leftNode = this->left;
        this->left = leftNode->right;
        leftNode->right = this;
        return leftNode;
    }

    SearchTreeNode * leftRotate() {
        SearchTreeNode * rightNode = this->right;
        this->right = rightNode->left;
        rightNode->left = this;
        return rightNode;
    }

    // void balance(SearchTreeNode * node) {
    //     int balance;
    //     if (node->right == nullptr && node->left != nullptr) {
    //         balance = -node->left->height();
    //     }
    //     else if (node->right != nullptr && node->left == nullptr) {
    //         balance = node->right->height();
    //     }
    //     else if (node->right != nullptr && node->left != nullptr) {
    //         balance = node->right->height() - node->left->height();
    //     }
    //     else if (node->right != nullptr && node->left == nullptr) {
    //         balance = 0;
    //     }

    //     SearchTreeNode* balanceNode;

    //     switch (balance)
    //     {
    //     case -2 :
    //         balanceNode = node->left;
    //         if (balanceNode->right == nullptr && balanceNode->left != nullptr) {
    //             balance = -balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = balanceNode->right->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left != nullptr) {
    //             balance = balanceNode->right->height() - balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = 0;
    //         }

    //         switch (balance)
    //         {
    //         case -1 :
    //             node = node->rightRotate();
    //             break;
    //         case 1 :
    //             node->left = balanceNode->leftRotate();
    //             node = node->rightRotate();
    //             break;
    //         }
    //         break;
    //     case 2 :
    //         balanceNode = node->right;
    //         if (balanceNode->right == nullptr && balanceNode->left != nullptr) {
    //             balance = -balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = balanceNode->right->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left != nullptr) {
    //             balance = balanceNode->right->height() - balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = 0;
    //         }

    //         switch (balance)
    //         {
    //         case -1 :
    //             node->right = balanceNode->rightRotate();
    //             node = node->leftRotate();
    //             break;
    //         case 1 :
    //             node = node->leftRotate();
    //             break;
    //         }
    //         break;
    //     }
    // }

    SearchTreeNode* balance(SearchTreeNode * node) {
        int leftHeight = -1, rightHeight = -1;
        if (node->left != nullptr) {
            leftHeight = node->left->height();
        }
        if (node->right != nullptr) {
            rightHeight = node->right->height();
        }

        int balanceFactor = rightHeight - leftHeight;

        switch (balanceFactor)
        {
        case -2:
            {
                int leftLeftHeight = -1, leftRightHeight = -1;
                if (node->left->left != nullptr) {
                    leftLeftHeight = node->left->left->height();
                }
                if (node->left->right != nullptr) {
                    leftRightHeight = node->left->right->height();
                }

                int balanceFactorLeft = leftRightHeight - leftLeftHeight;

                if (balanceFactorLeft > 0) {
                    node->left = node->left->leftRotate();
                }
                return node->rightRotate();
                break;
            }
        
        case 2:
            {
                int rightLeftHeight = -1, rightRightHeight = -1;
                if (node->right->left != nullptr) {
                    rightLeftHeight = node->right->left->height();
                }
                if (node->right->right != nullptr) {
                    rightRightHeight = node->right->right->height();
                }

                int balanceFactorRight = rightRightHeight - rightLeftHeight;

                if (balanceFactorRight < 0) {
                    node->right = node->right->rightRotate();
                }
                return node->leftRotate();
                break;
            }
        }
        return 0;
    }

    // void balanceRight() {
    //     int balance;
    //     if (this->right->right == nullptr && this->right->left != nullptr) {
    //         balance = -this->right->left->height();
    //     }
    //     else if (this->right->right != nullptr && this->right->left == nullptr) {
    //         balance = this->right->right->height();
    //     }
    //     else if (this->right->right != nullptr && this->right->left != nullptr) {
    //         balance = this->right->right->height() - this->right->left->height();
    //     }
    //     else if (this->right->right != nullptr && this->right->left == nullptr) {
    //         balance = 0;
    //     }

    //     SearchTreeNode* balanceNode;

    //     switch (balance)
    //     {
    //     case -2 :
    //         balanceNode = this->right->left;
    //         if (balanceNode->right == nullptr && balanceNode->left != nullptr) {
    //             balance = -balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = balanceNode->right->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left != nullptr) {
    //             balance = balanceNode->right->height() - balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = 0;
    //         }

    //         switch (balance)
    //         {
    //         case -1 :
    //             this->right->left = balanceNode->rightRotate();
    //             break;
    //         case 1 :
    //             this->right->left = balanceNode->leftRotate();
    //             this->right = this->right->rightRotate();
    //             break;
    //         }
    //         break;
    //     case 2 :
    //         balanceNode = this->right->right;
    //         if (balanceNode->right == nullptr && balanceNode->left != nullptr) {
    //             balance = -balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = balanceNode->right->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left != nullptr) {
    //             balance = balanceNode->right->height() - balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = 0;
    //         }

    //         switch (balance)
    //         {
    //         case -1 :
    //             this->right->right = balanceNode->rightRotate();
    //             this->right = this->right->leftRotate();
    //             break;
    //         case 1 :
    //             this->right->right = balanceNode->leftRotate();
    //             break;
    //         }
    //         break;
    //     }
    // }

    // void balanceLeft() {
    //     int balance;
    //     if (this->left->right == nullptr && this->left->left != nullptr) {
    //         balance = -this->left->left->height();
    //     }
    //     else if (this->left->right != nullptr && this->left->left == nullptr) {
    //         balance = this->left->right->height();
    //     }
    //     else if (this->left->right != nullptr && this->left->left != nullptr) {
    //         balance = this->left->right->height() - this->left->left->height();
    //     }
    //     else if (this->left->right != nullptr && this->left->left == nullptr) {
    //         balance = 0;
    //     }

    //     SearchTreeNode* balanceNode;

    //     switch (balance)
    //     {
    //     case -2 :
    //         balanceNode = this->left->left;
    //         if (balanceNode->right == nullptr && balanceNode->left != nullptr) {
    //             balance = -balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = balanceNode->right->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left != nullptr) {
    //             balance = balanceNode->right->height() - balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = 0;
    //         }

    //         switch (balance)
    //         {
    //         case -1 :
    //             this->left->left = balanceNode->rightRotate();
    //             break;
    //         case 1 :
    //             this->left->left = balanceNode->leftRotate();
    //             this->left = this->left->rightRotate();
    //             break;
    //         }
    //         break;
    //     case 2 :
    //         balanceNode = this->left->right;
    //         if (balanceNode->right == nullptr && balanceNode->left != nullptr) {
    //             balance = -balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = balanceNode->right->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left != nullptr) {
    //             balance = balanceNode->right->height() - balanceNode->left->height();
    //         }
    //         else if (balanceNode->right != nullptr && balanceNode->left == nullptr) {
    //             balance = 0;
    //         }

    //         switch (balance)
    //         {
    //         case -1 :
    //             this->left->right = balanceNode->rightRotate();
    //             this->left = this->left->leftRotate();
    //             break;
    //         case 1 :
    //             this->left->right = balanceNode->leftRotate();
    //             break;
    //         }
    //         break;
    //     }
    // }

    SearchTreeNode* insertNumberBalanced(int value) {
        // create a new node and insert in the tree while keeping it balanced
        if (value >= this->value) {
            if (this->right == nullptr) {
                this->right = new SearchTreeNode(value);
            }
            else {
                this->right = this->right->insertNumberBalanced(value);
            }
        }
        else {
            if (this->left == nullptr) {
                this->left = new SearchTreeNode(value);
            }
            else {
                this->left = this->left->insertNumberBalanced(value);
            }
        }
        
        // if (this->right->height() - this->left->height() >= 2) {
        //     this->balanceRight();
        // }
        // else if (this->right->height() - this->left->height() <= -2) {
        //     this->balanceLeft();
        // }

        return this->balance(this);
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
        stn = stn->insertNumberBalanced(rand()%20);
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
