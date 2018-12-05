#include "mainwindow.h"
#include "competition.h"
#include <QApplication>
#include <QVector>
int main(int argc, char *argv[])
{
    Competition c;
    QVector<Competition> vecComp;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
