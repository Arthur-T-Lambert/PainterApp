#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/en_US.qm");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
