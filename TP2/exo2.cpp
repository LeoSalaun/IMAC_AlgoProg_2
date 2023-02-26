// #include <QApplication>
// #include <time.h>

// #include "tp2.h"

// MainWindow* w=nullptr;

// void insertionSort(Array& toSort){
// 	Array& sorted=w->newArray(toSort.size());

// 	// insertion sort from toSort to sorted
	
// 	toSort=sorted; // update the original array
// }

// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
//     uint elementCount=15; // number of elements to sort
//     MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
//     w = new TestMainWindow(insertionSort); // window which display the behavior of the sort algorithm
// 	w->show();

// 	return a.exec();
// }


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

void insertionSort(int array[],int size){
	int result[size];
	result[0] = array[0];

	for (int i=1 ; i<size ; i++) {
		int j=0;
		while (result[j] <= array[i] && j<i) {
			j++;
		}
		if (j<i) {
			for (int k=i ; k>j ; k--) {
				result[k] = result[k-1];
			}
		}
		result[j] = array[i];
	}

	for (int i=0 ; i<size ; i++) {
		array[i] = result[i];
	}
}

int main() {
    int array[10] = {1,2,8,6,4,7,5,3,0,9};
    printArray(array,10);
    insertionSort(array,10);
    printArray(array,10);
}