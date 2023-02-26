// #include <QApplication>
// #include <time.h>

// #include "tp2.h"

// MainWindow* w = nullptr;

// void selectionSort(Array& toSort){
// 	// selectionSort
// }

// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
//     uint elementCount=15; // number of elements to sort
//     MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
//     w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
//     w->show();

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

void selectionSort(int array[], int size){
	for (int i=0 ; i<size-1 ; i++) {
        int min = i;
        for (int j=i+1 ; j<size ; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        exchange(array,i,min);
    }
}

int main() {
    int array[10] = {1,2,8,6,4,7,5,3,0,9};
    printArray(array,10);
    selectionSort(array,10);
    printArray(array,10);
}