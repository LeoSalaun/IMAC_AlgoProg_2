// #include "tp1.h"
// #include <QApplication>
// #include <time.h>

// #define return_and_display(result) return _.store(result);

// int fibonacci(int value)
// {
//     Context _("fibonacci", value); // do not care about this, it allow the display of call stack

//     // your code

//     return_and_display(value);
// }

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);  // create a window manager
//     MainWindow::instruction_duration = 400;  // make a pause between instruction display
//     MainWindow* w = new FibonacciWindow(fibonacci); // create a window for this exercice
//     w->show(); // show exercice

//     return a.exec(); // main loop while window is opened
// }

#include <iostream>
using namespace std;

long fibonacci(int value) {
    if (value == 0) {
        return 0;
    }
    else if (value == 1) {
        return 1;
    }
    else {
        return fibonacci(value-1) + fibonacci(value-2);
    }
}

int main(int argc, char *argv[]) {
    cout << fibonacci(atoi(argv[1])) << endl;
}