#ifndef JUDGEPAGE_H
#define JUDGEPAGE_H

#include <QWidget>
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <QDragEnterEvent>
#include <QMimeData>
#include <judgethread.h>

namespace Ui {
class JudgePage;
}

class JudgePage : public QWidget
{
    Q_OBJECT

public:
    explicit JudgePage(QWidget *parent = nullptr);
    ~JudgePage();
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void on_pushButton_clicked();
    int scan_dir(std::string folderpath,std::string* folders);

    void on_CloseBtn_clicked();

private:
    Ui::JudgePage *ui;
    bool Uploaded=false;
    std::string folderpath;

};

#endif // JUDGEPAGE_H
