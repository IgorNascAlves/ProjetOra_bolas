#include "mainwindow.h"
#include <QApplication>
#include <cstdlib>
#include <iostream>

#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //return 0;
    return a.exec();
}
