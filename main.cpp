#include "MainWindow.h"

#include <QApplication>

#include <data/DataManager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataManager::init();

    MainWindow w;
    w.show();
    return a.exec();
}
