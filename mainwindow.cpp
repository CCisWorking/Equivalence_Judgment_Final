#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *father_,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    father = father_;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_JudgeBtn_clicked()
{
//    this->close();
    JudgePage *judgepg=new JudgePage(this);
    judgepg->show();
}


void MainWindow::on_CloseBtn_clicked()
{
    this->close();
    father->quit();
}

void MainWindow::closeEvent( QCloseEvent * event )
{
switch( QMessageBox::information( this, tr("exit tip"), tr("Do you really want exit?"), tr("Yes"), tr("No"), 0, 1 ) )
   {
     case 0:
          event->accept();
          break;
     case 1:
     default:
         event->ignore();
         break;
   }
}


void MainWindow::on_ShowResult_clicked()
{
    ResultPage *resultpg=new ResultPage(this);
    resultpg->show();
}


void MainWindow::on_CompareBtn_clicked()
{
    ComparePage *comparepg=new ComparePage(this);
    comparepg->show();
}


void MainWindow::on_HumanResult_clicked()
{
    HumanResultPage *humanpag=new HumanResultPage();
    humanpag->show();
}

