#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <iostream>

namespace Ui {
class ResultPage;
}

class ResultPage : public QWidget
{
    Q_OBJECT

public:
    explicit ResultPage(QWidget *parent = nullptr);
    ~ResultPage();

private slots:
    void on_CloseBtn_clicked();

private:
    Ui::ResultPage *ui;
    void show_re(int path);
};

#endif // RESULTPAGE_H
