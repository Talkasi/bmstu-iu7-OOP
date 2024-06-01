#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Ваш комфорт — наша профессия!");
    w.show();
    return a.exec();
}
