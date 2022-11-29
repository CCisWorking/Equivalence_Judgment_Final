#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(&a);
    w.setWindowTitle("JudgeTool");
    w.show();
    return a.exec();
}
