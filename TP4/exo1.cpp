// #include "tp4.h"
// #include "mainwindow.h"

// #include <QApplication>
// #include <time.h>
// #include <stdio.h>

// MainWindow* w = nullptr;
// using std::size_t;
// using std::string;


#include <iostream>
using namespace std;

void printArray(int array[],int size) {
    cout << "- ";
    for (int i=0; i<size; i++)
    {
        cout << array[i] << " - ";
    }
    cout << endl;
}

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
	for (int i=nodeIndex ; i<2*nodeIndex+1 && i<heapSize ; i++) {
		if (heap[i] > heap[i_max]) {
			i_max = i;
		}
	}

	if (i_max != nodeIndex) {
		exchange(heap,nodeIndex,i_max);
		heapify(heap,heapSize,i_max);
	}
}

void buildHeap(int * heap, int * heapSize, int * numbers, int size)
{
	for (int i=0 ; i<size ; i++) {
		insertHeapNode(heap,heapSize,numbers[i]);
	}

	// heap = numbers;
	// *heapSize = size;
	// for (int i=0 ; i<size ; i++) {
	// 	heapify(heap,*heapSize,i);
	// }
}

void heapSort(int * heap, int heapSize)
{
	for (int i=heapSize-1 ; i>=0 ; i--) {
		exchange(heap,i,0);
		heapify(heap,heapSize,i);
	}
}

int main(int argc, char *argv[])
{
	int heap[10];
	int heapSize = 0;
	int numbers[10] = {1,58,2,8,4,5,6,54,75,98};

	printArray(numbers,10);

	buildHeap(heap,&heapSize,numbers,10);

	printArray(heap,heapSize);

	heapSort(heap,heapSize);

	printArray(heap,heapSize);

	// QApplication a(argc, argv);
    // MainWindow::instruction_duration = 50;
    // w = new HeapWindow();
	// w->show();

	// return a.exec();
}
