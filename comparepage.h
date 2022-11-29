#ifndef COMPAREPAGE_H
#define COMPAREPAGE_H

#include <QWidget>
#include <iostream>
#include <fstream>

namespace Ui {
class ComparePage;
}

class ComparePage : public QWidget
{
    Q_OBJECT

public:
    explicit ComparePage(QWidget *parent = nullptr);
    ~ComparePage();

private slots:
    void on_CloseBtn_clicked();

    void on_CompareBtn_clicked();

    void on_Equal_clicked();

    void on_Inequal_clicked();

    void on_Doubtful_clicked();

    void on_Before_clicked();

    void on_Next_clicked();

private:
    Ui::ComparePage *ui;
    void read_same();
    int cnt_same=0;
    std::string same[30][4];
    int now=0;
    int findnxt_same(std::string cur,std::string l2[70],int r2,int r2max);
    void show_txt();
    int human_re[30]; // 1:equal 2:inequal 3:doubtful
    void Show_();
    void Get_re();
};

#endif // COMPAREPAGE_H
