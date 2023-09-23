#include "mainwindow.h"
#include <QLabel>
#include <QString>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //QLabel *label = new QLabel("Конвертер");
    //label->show();
    w.show();
    return a.exec();
}
