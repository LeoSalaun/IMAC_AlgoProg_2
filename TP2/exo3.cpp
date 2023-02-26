// #include <QApplication>
// #include <time.h>

// #include "tp2.h"

// MainWindow* w=nullptr;


// void bubbleSort(Array& toSort){
// 	// bubbleSort
// }


// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
// 	uint elementCount=20;
// 	MainWindow::instruction_duration = 100;
// 	w = new TestMainWindow(bubbleSort);
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

void bubbleSort(int array[],int size){
	for (int i=size ; i>=0 ; i--) {
		for (int j=i ; j<size-1 ; j++) {
			if (array[j] > array[j+1]) {
				exchange(array,j,j+1);
			}
		}
	}
}

int main() {
    int array[10] = {1,2,8,6,4,7,5,3,0,9};
    printArray(array,10);
    bubbleSort(array,10);
    printArray(array,10);
}