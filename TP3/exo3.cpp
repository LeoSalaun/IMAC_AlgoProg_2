// #include "mainwindow.h"
// #include "tp3.h"
// #include <QApplication>
// #include <time.h>
// #include <stack>
// #include <queue>

// MainWindow* w = nullptr;
// using std::size_t;

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
                this->right = createNode(value);
            }
            else {
                this->right->insertNumber(value);
            }
        }
        else {
            if (this->left == nullptr) {
                this->left = createNode(value);
            }
            else {
                this->left->insertNumber(value);
            }
        }
    }

	int height() const	{
        // should return the maximum height between left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        int somme = 1, heightRight, HeightLeft;
        if (this->right != nullptr) {
            int heightRight = this->right->height();
        }
        else {
            heightRight = 0;
        }
        if (this->left != nullptr) {
            int HeightLeft = this->left->height();
        }
        else {
            HeightLeft = 0;
        }
        somme += max(heightRight,HeightLeft);  // MAX À DÉFINIR
        
        return somme;
    }

	int nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        return 1;
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        return false;
	}

	void allLeaves(SearchTreeNode* leaves[], int* leavesCount) {
        // fill leaves array with all leaves of this tree
	}

	void inorderTravel(SearchTreeNode* nodes[], int* nodesCount) {
        // fill nodes array with all nodes with inorder travel
	}

	void preorderTravel(SearchTreeNode* nodes[], int* nodesCount) {
        // fill nodes array with all nodes with preorder travel
	}

	void postorderTravel(SearchTreeNode* nodes[], int* nodesCount) {
        // fill nodes array with all nodes with postorder travel
	}

	SearchTreeNode* find(int value) {
        // find the node containing value
		return nullptr;
	}

    void reset()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
        left = right = nullptr;
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

int main(int argc, char *argv[])
{
	// QApplication a(argc, argv);
	// MainWindow::instruction_duration = 200;
    // w = new BinarySearchTreeWindow<SearchTreeNode>();
	// w->show();

	// return a.exec();
}
