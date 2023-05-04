// #include <QApplication>
// #include <time.h>
// #include "tp2.h"

// MainWindow* w=nullptr;

// void merge(Array& first, Array& second, Array& result);

// void splitAndMerge(Array& origin)
// {
// 	// stop statement = condition + return (return stop the function even if it does not return anything)

// 	// initialisation
// 	Array& first = w->newArray(origin.size()/2);
// 	Array& second = w->newArray(origin.size()-first.size());
	
// 	// split

// 	// recursiv splitAndMerge of lowerArray and greaterArray

// 	// merge
// }

// void merge(Array& first, Array& second, Array& result)
// {

// }

// void mergeSort(Array& toSort)
// {
//     splitAndMerge(toSort);
// }

// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
// 	MainWindow::instruction_duration = 50;
//     w = new TestMainWindow(mergeSort);
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

void merge(int first[], int second[], int result[], int sizeFirst, int sizeSecond)
{
	int indexFirst = 0, indexSecond = 0;
	cout << "-- merge --" << endl;
	printArray(first,sizeFirst);
	printArray(second,sizeSecond);
	/*for (int i=0 ; i<sizeFirst+sizeSecond ; i++) {
		if (indexFirst == sizeFirst && indexSecond < sizeSecond) {
			result[i] = second[indexSecond];
			indexSecond++;
		}
		else if (indexFirst < sizeFirst && indexSecond == sizeSecond) {
			result[i] = first[indexFirst];
			indexFirst++;
		}
		if (first[indexFirst] < second[indexSecond]) {
			result[i] = first[indexFirst];
			indexFirst++;
		}
		else {
			result[i] = second[indexSecond];
			indexSecond++;
		}
	}*/
	while (indexFirst < sizeFirst || indexSecond < sizeSecond) {
		if (first[indexFirst] <= second[indexSecond] && indexFirst < sizeFirst) {
			result[indexFirst+indexSecond] = first[indexFirst];
			indexFirst++;
		}
		else if (indexSecond < sizeSecond) {
			result[indexFirst+indexSecond] = second[indexSecond];
			indexSecond++;
		}
	}
	/*if (indexFirst < sizeFirst) {
		for (int i=indexFirst ; i<sizeFirst ; i++) {
			result[indexFirst+indexSecond] = first[indexFirst];
		}
	}
	else if (indexSecond < sizeSecond) {
		for (int i=indexSecond ; i<sizeSecond ; i++) {
			result[indexFirst+indexSecond] = second[indexSecond];
		}	
	}*/
}

void splitAndMerge(int origin[], int size)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)

	if (size == 1) {
		return;
	}
	else {
		int first[size/2];
		int second[size-size/2];
		for (int i=0 ; i<size ; i++) {
			if (i<size/2) {
				first[i] = origin[i];
			}
			else {
				second[i-size/2] = origin[i];
			}
		}
		cout << "-- split --" << endl;
		printArray(first,size/2);
		printArray(second,size-size/2);
		splitAndMerge(first,size/2);
		splitAndMerge(second,size-size/2);

		merge(first,second,origin,size/2,size-size/2);
		printArray(origin,size);
	}

	// initialisation
	// Array& first = w->newArray(origin.size()/2);
	// Array& second = w->newArray(origin.size()-first.size());
	
	// split

	// recursiv splitAndMerge of lowerArray and greaterArray

	// merge
}

void mergeSort(int toSort[], int sizeSort)
{
    splitAndMerge(toSort, sizeSort);
}

int main() {
    int array[10] = {1,2,8,6,4,7,5,3,0,9};
    printArray(array,10);
    mergeSort(array,10);
    printArray(array,10);
}