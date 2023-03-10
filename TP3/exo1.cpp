/*#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

int binarySearch(Array& array, int toSearch)
{
	return -1;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchWindow(binarySearch);
	w->show();

	return a.exec();
}*/

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
	while (indexFirst < sizeFirst && indexSecond < sizeSecond) {
		if (first[indexFirst] <= second[indexSecond]) {
			result[indexFirst+indexSecond] = first[indexFirst];
			indexFirst++;
		}
		else {
			result[indexFirst+indexSecond] = second[indexSecond];
			indexSecond++;
		}
	}
	if (indexFirst < sizeFirst) {
		for (int i=indexFirst ; i<sizeFirst ; i++) {
			result[indexFirst+indexSecond] = first[indexFirst];
		}
	}
	else if (indexSecond < sizeSecond) {
		for (int i=indexSecond ; i<sizeSecond ; i++) {
			result[indexFirst+indexSecond] = second[indexSecond];
		}	
	}
}

void splitAndMerge(int origin[], int size)
{
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
		splitAndMerge(first,size/2);
		splitAndMerge(second,size-size/2);

		merge(first,second,origin,size/2,size-size/2);
	}
}

void mergeSort(int toSort[], int sizeSort)
{
    splitAndMerge(toSort, sizeSort);
}

int binarySearch(int array[], int size, int toSearch)
{
	mergeSort(array,size);
	int debut = 0, fin = size, milieu = (debut+fin)/2;
	bool trouve = array[milieu] == toSearch;
	while (!(trouve) && debut<fin) {
		if (toSearch > array[milieu]) {
			debut = milieu+1;
		}
		else {
			fin = milieu-1;
		}
		milieu = (debut+fin)/2;
		trouve = array[milieu] == toSearch;
	}
	if (trouve) {
		return milieu;
	}
	return -1;
}

int main(int argc, char ** argv) {
    int array[10] = {1,2,8,6,4,7,5,3,0,9};
    printArray(array,10);
	int trouve = binarySearch(array,10,atoi(argv[1]));
	if (trouve == -1) {
		cout << "Pas trouvé" << endl;
	}
	else {
		cout << "Trouvé à l'indice : " << trouve << endl;
	}
}
