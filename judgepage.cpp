#include "judgepage.h"
#include "ui_judgepage.h"

JudgePage::JudgePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JudgePage)
{
    ui->setupUi(this);
//    setAcceptDrops(true);
    this->setAcceptDrops(true);
}

JudgePage::~JudgePage()
{
    delete ui;
}


void JudgePage::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void JudgePage::dropEvent(QDropEvent *event)
{
    QString name = event->mimeData()->urls().first().toString();
    ui->FileToHere->setText(name);
//    std::cerr<<name.toStdString().erase(0,7)<<std::endl;
    Uploaded=true;
    folderpath=name.toStdString().erase(0,7);
//    std::cerr<<"folderpath:"<<folderpath<<std::endl;
    //file:///Users/cc/Library/Mobile Documents/com~apple~CloudDocs/mac2022/大三上2022-2023fall/软件工程/lab4/input/
}

void JudgePage::on_pushButton_clicked()
{
    std::string folders[20];
    std::string files[20][20];// user/sdnasdn/.../input/dasd/sadais.cpp
    std::string files_name[20][20]; // sadais.cpp
    std::string files_path[20][20]; // /input/dasd/sadais.cpp
    int folders_files_cnt[20];
    if(Uploaded){
        int cnt=this->scan_dir(folderpath,folders);
        for(int i=0;i<cnt;i++){
//            std::cerr<<"folder:"<<folders[i]<<std::endl;
            std::string tmp(folderpath);
            std::string tmp_(folders[i]);
            tmp.append(tmp_.append("/"));
            folders_files_cnt[i]=this->scan_dir(tmp,files[i]);
            for(int j=0;j <folders_files_cnt[i];j++){
                files_name[i][j]=files[i][j];
                files_path[i][j]="input/"+tmp_+files[i][j];
                files[i][j]=tmp+files[i][j];
            }
        }
        JudgeThread jt(folderpath,folders,cnt,files,files_path,files_name,folders_files_cnt);
        this->close();
    }
}

static int filterDot(const struct dirent * dir) {
    if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, ".DS_Store") == 0
            ||strcmp(dir->d_name, "stdin_format.txt") == 0) {
        // 过滤掉 ".",".DS_Store","stdin_format.txt"和".."
        return 0;
    } else {
        return 1;
    }
}

int JudgePage::scan_dir(std::string folderpath,std::string* folders){
    struct dirent **namelist;
    int n;
    const char *path = folderpath.c_str();
    n = scandir(path, &namelist, filterDot, alphasort);
    if (n < 0) {
        perror("scandir");
    } else {
        int idx = 0;
        while (idx !=n) {
            folders[idx]=namelist[idx]->d_name;
            free(namelist[idx]);
            idx ++;
        }
        free(namelist);
        return idx;
    }
}


void JudgePage::on_CloseBtn_clicked()
{
    this->close();
}

