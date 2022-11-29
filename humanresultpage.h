#ifndef HUMANRESULTPAGE_H
#define HUMANRESULTPAGE_H

#include <QWidget>
#include <QFile>

namespace Ui {
class HumanResultPage;
}

class HumanResultPage : public QWidget
{
    Q_OBJECT

public:
    explicit HumanResultPage(QWidget *parent = nullptr);
    ~HumanResultPage();

private slots:
    void on_CloseBtn_clicked();

private:
    Ui::HumanResultPage *ui;
    void show_re(int path);
};

#endif // HUMANRESULTPAGE_H
