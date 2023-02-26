// #include <QApplication>
// #include <time.h>

// #include "tp2.h"

// MainWindow* w = nullptr;

// void slow_sort(Array& toSort){
//     for (uint i=0; i<toSort.size(); i++)
//     {
//         for (uint j=0; j<toSort.size(); j++)
//         {
//             if (toSort[j] > toSort[i])
//                 toSort.swap(i, j);
//         }
//     }
// }

// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
//     MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
//     w = new TestMainWindow(slow_sort); // window which display the behavior of the sort algorithm
//     w->show();

// 	return a.exec();
// }

#include <iostream>
using namespace std;


void slow_sort(int array[], int size){
    int temp;
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            if (array[j] > array[i]) {
                temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }
}

void printArray(int array[],int size) {
    cout << "- ";
    for (int i=0; i<size; i++)
    {
        cout << array[i] << " - ";
    }
    cout << endl;
}

int main(int argc, char ** argv) {
    int array[10] = {1,2,8,6,4,7,5,3,4};
    printArray(array,10);
    slow_sort(array,10);
    printArray(array,10);
}