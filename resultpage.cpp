#include "resultpage.h"
#include "ui_resultpage.h"

ResultPage::ResultPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultPage)
{
    ui->setupUi(this);
//    QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开文件"),
//            "", tr("file(*.csv)"));
    ui->eq->setColumnCount(2);
    ui->eq->setRowCount(100);
    this->show_re(1);
    this->show_re(2);
}

void ResultPage::show_re(int path){
    std::cerr<<"path:"<<path;
    ui->neq->setColumnCount(2);
    ui->neq->setRowCount(100);
    QString p2("/Users/cc/Desktop/inequal.csv");
    QString p1("/Users/cc/Desktop/equal.csv");
    QFile file;
    if(path==1) file.setFileName(p1);
    else file.setFileName(p2);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream  in(&file);
    QString line;
    QStringList fields;
    int row  = 0;
    while(!in.atEnd()){
        line = in.readLine();
        fields = line.split(',');
        for(int column = 0; column<fields.size();column++){
            if(path==1)
                ui->eq->setItem(row, column, new QTableWidgetItem(fields[column]));
            else
                ui->neq->setItem(row, column, new QTableWidgetItem(fields[column]));
        }
        row++;
    }
    QStringList headers;
    headers << QStringLiteral("file1") << QStringLiteral("file2");
    if(path==1){
        ui->eq->setHorizontalHeaderLabels(headers);
        ui->eq->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->eq->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->eq->resizeColumnToContents(10);
        ui->eq->update();
    }
    else{
        ui->neq->setHorizontalHeaderLabels(headers);
        ui->neq->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->neq->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->neq->resizeColumnToContents(10);
        ui->neq->update();
    }

}

ResultPage::~ResultPage()
{
    delete ui;
}

void ResultPage::on_CloseBtn_clicked()
{
    this->close();
}

