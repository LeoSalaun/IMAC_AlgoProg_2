// #include "tp4.h"
// #include "mainwindow.h"

// #include <QApplication>
// #include <time.h>
// #include <stdio.h>

// MainWindow* w = nullptr;
// using std::size_t;
// using std::string;

void exchange(int array[], int i, int j) {
    int temp = array[j];
    array[j] = array[i];
    array[i] = temp;
}

int leftChild(int * heap, int nodeIndex)
{
    return heap[2*nodeIndex+1];
}

int rightChild(int * heap, int nodeIndex)
{
    return heap[2*nodeIndex+2];
}

void insertHeapNode(int * heap, int * heapSize, int value)
{
	// use (*this)[i] or this->get(i) to get a value at index i
	int i = *heapSize;
	heap[i] = value;
	while (i>0 && heap[i] > heap[(i-1)/2]) {
		exchange(heap,i,(i-1)/2);
		i = (i-1)/2;
	}
	(*heapSize)++;
}

void heapify(int * heap, int heapSize, int nodeIndex)
{
	// use (*this)[i] or this->get(i) to get a value at index i
	int i_max = nodeIndex;
}

void buildHeap(int * heap, int * numbers)
{

}

void heapSort(int * heap)
{

}

int main(int argc, char *argv[])
{
	int * heap;
	// QApplication a(argc, argv);
    // MainWindow::instruction_duration = 50;
    // w = new HeapWindow();
	// w->show();

	// return a.exec();
}
