#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QMimeData>
#include <iostream>
#include <QDebug>
#include <judgepage.h>
#include <QMessageBox>
#include <resultpage.h>
#include <comparepage.h>
#include <humanresultpage.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *father_,QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent( QCloseEvent * event );

private slots:
    void on_JudgeBtn_clicked();

    void on_CloseBtn_clicked();

    void on_ShowResult_clicked();

    void on_CompareBtn_clicked();

    void on_HumanResult_clicked();

private:
    Ui::MainWindow *ui;
    QApplication *father;

};
#endif // MAINWINDOW_H
