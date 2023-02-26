// #include <QApplication>
// #include <time.h>

// #include "tp2.h"


// MainWindow* w=nullptr;

// void recursivQuickSort(Array& toSort, int size)
// {
// 	// stop statement = condition + return (return stop the function even if it does not return anything)
	
// 	Array& lowerArray = w->newArray(size);
// 	Array& greaterArray= w->newArray(size);
// 	int lowerSize = 0, greaterSize = 0; // effectives sizes

// 	// split
	
// 	// recursiv sort of lowerArray and greaterArray

// 	// merge
// }

// void quickSort(Array& toSort){
// 	recursivQuickSort(toSort, toSort.size());
// }


// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
// 	uint elementCount=20;
// 	MainWindow::instruction_duration = 50;
//     w = new TestMainWindow(quickSort);
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

void quickSort(int array[],int size){
	//printArray(array,size);
	if (size > 1) {
		int pivot = size/2, size1 = 0, size2 = 0;

		//cout << pivot << " -> " << array[pivot] << endl;

		int array1[size];
		int array2[size];

		for (int i=0 ; i<size ; i++) {
			if (array[i] <= array[pivot]) {
				array1[size1] = array[i];
				size1++;
				//cout << "coucou" << endl;
			}
			else {
				array2[size2] = array[i];
				size2++;
				cout << "hello" << endl;
			}
		}
		//cout << size << " - " << size1 << " - " << size2 << endl;

		quickSort(array1,size1);
		quickSort(array2,size2);

		for (int i=0 ; i<size ; i++) {
			if (i<=size1) {
				array[i] = array1[i];
			}
			else {
				array[i] = array2[i-size1];
			}
		}
	}
}

int main() {
    int array[10] = {1,2,8,6,4,7,5,3,0,9};
    printArray(array,10);
    quickSort(array,10);
    printArray(array,10);
}