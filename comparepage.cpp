#include "comparepage.h"
#include "ui_comparepage.h"

ComparePage::ComparePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComparePage)
{
    ui->setupUi(this);
    this->read_same();
    this->show_txt();
    this->Get_re();

//    ui->Num->setText(QString::number(now+1));
//    ui->File1->setText(QString::fromStdString(same[now][2]));
//    ui->File2->setText(QString::fromStdString(same[now][3]));
    this->Show_();
}

void ComparePage::Get_re(){
    std::ifstream f;
    f.open("/Users/cc/Desktop/human_re.csv", std::ios::in);
    int i=0;
    while(f){
        f>>human_re[i];
        i+=1;
    }
    for(;i<cnt_same;i++){
        human_re[i]=3;
//        std::cerr<<same[i][2]<<" "<<same[i][3]<<std::endl;
    }
    f.close();
}

void ComparePage::Show_(){
    ui->Num->setText(QString::number(now+1));
    ui->File1->setText(QString::fromStdString(same[now][2]));
    ui->File2->setText(QString::fromStdString(same[now][3]));
    if(human_re[now]==1){
        ui->Re->setText("Equal");
    }
    else if(human_re[now]==2){
        ui->Re->setText("Inequal");
    }
    else{
        ui->Re->setText("Doubtful");
    }
}

void ComparePage::show_txt(){
    if(now >= cnt_same) {
        now-=1;
//        ui->Num->setText(QString::number(now+1));
//        ui->File1->setText(QString::fromStdString(same[now][2]));
//        ui->File2->setText(QString::fromStdString(same[now][3]));
        this->Show_();
    }
    else{
        if(now < 0) {
            now=0;
//            ui->Num->setText(QString::number(now+1));
//            ui->File1->setText(QString::fromStdString(same[now][2]));
//            ui->File2->setText(QString::fromStdString(same[now][3]));
            this->Show_();
        }
        std::ifstream f1;
        std::ifstream f2;
        f1.open(same[now][0], std::ios::in);
        f2.open(same[now][1], std::ios::in);
        std::string line1;
        std::string line2;
        std::string l1[70];
        std::string l2[70];
        int c1=0;
        int c2=0;
        ui->w1->clear();
        ui->w2->clear();
        while(getline(f1,line1)){
            QString to1=QString::fromStdString(std::to_string(c1+1)+"  "+line1);
            ui->w1->insertItem(c1,to1);
            c1+=1;
        }
        while(getline(f2,line2)){
            QString to2=QString::fromStdString(std::to_string(c2+1)+"  "+line2);
            ui->w2->insertItem(c2,to2);
            c2+=1;
        }
        f1.close();
        f2.close();
    }
}

ComparePage::~ComparePage()
{
    delete ui;
}

void ComparePage::on_CloseBtn_clicked()
{
    std::ofstream f;
    f.open("/Users/cc/Desktop/human_equal.csv", std::ios::out);
    f<<"file1"<<","<<"file2"<<std::endl;
    for(int i=0;i<cnt_same;i++){
        if(human_re[i]==1){
            f<<same[i][2]<<",";
            f<<same[i][3]<<std::endl;
        }
//        std::cerr<<same[i][2]<<" "<<same[i][3]<<std::endl;
    }
    f.close();

    std::ofstream f2;
    f2.open("/Users/cc/Desktop/human_inequal.csv", std::ios::out);
    f2<<"file1"<<","<<"file2"<<std::endl;
    for(int i=0;i<cnt_same;i++){
        if(human_re[i]==2){
            f2<<same[i][2]<<",";
            f2<<same[i][3]<<std::endl;
        }
//        std::cerr<<same[i][2]<<" "<<same[i][3]<<std::endl;
    }
    f2.close();

    std::ofstream f3;
    f3.open("/Users/cc/Desktop/human_re.csv");
    for(int i=0;i<cnt_same;i++){
        f3<<human_re[i]<<std::endl;
//        std::cerr<<same[i][2]<<" "<<same[i][3]<<std::endl;
    }
    f3.close();
    this->close();
}


void ComparePage::on_CompareBtn_clicked()
{
//    ui->listWidget2->item(i)->setForeground(QColor("red"));

    std::ifstream f1;
    std::ifstream f2;
    f1.open(same[now][0], std::ios::in);
    f2.open(same[now][1], std::ios::in);
    std::string line1;
    std::string line2;
    std::string l1[70];
    std::string l2[70];
    int cnt1=0;
    int cnt2=0;
    while(getline(f1,line1)){
        l1[cnt1]=line1;
        cnt1+=1;
    }
    while(getline(f2,line2)){
        l2[cnt2]=line2;
        cnt2+=1;
    }
    int c1=0;
    int c2=0;
    int r1=0;
    int r2=0;
    f1.close();
    f2.close();
    ui->w1->clear();
    ui->w2->clear();
    while(c1 < cnt1 && c2 < cnt2){
        int n;
        if(l1[c1].compare(l2[c2]) == 0){
            QString to1=QString::fromStdString(std::to_string(r1+1)+"  "+l1[c1]);
            ui->w1->insertItem(r1,to1);
            r1+=1;
            QString to2=QString::fromStdString(std::to_string(r2+1)+"  "+l2[c2]);
            ui->w2->insertItem(r2,to2);
            r2+=1;

            c1+=1;
            c2+=1;
            std::cerr<<"same line"<<c1<<" "<<c2<<std::endl;
        }
        else if(this->findnxt_same(l1[c1],l2,c2,cnt2)!=-1){
            n=this->findnxt_same(l1[c1],l2,c2,cnt2);
            for(int i=0;i<n-c2;i++){
                std::string tmp=std::to_string(r1+1)+"  ";
                ui->w1->insertItem(r1,QString::fromStdString(tmp));
                QBrush br;
                br.setColor(QColor(190,190,190));
                br.setStyle(Qt::FDiagPattern);
                ui->w1->item(r1)->setBackground(br);
                r1+=1;
                std::cerr<<"add1 :"<<r1<<std::endl;
            }
            for(int i=c2;i<n;i++){
                QString to2=QString::fromStdString(std::to_string(r2+1)+"  "+l2[c2]);
                ui->w2->insertItem(r2,to2);
                ui->w2->item(r2)->setForeground(QColor("red"));
                r2+=1;
                c2+=1;
            }
        }
        else if(this->findnxt_same(l2[c2],l1,c1,cnt1)!=-1){
            n=this->findnxt_same(l2[c2],l1,c1,cnt1);
            for(int i=0;i<n-c1;i++){
                std::string tmp=std::to_string(r2+1)+"  ";
                ui->w2->insertItem(r2,QString::fromStdString(tmp));
                QBrush br;
                br.setColor(QColor(190,190,190));
                br.setStyle(Qt::FDiagPattern);
                ui->w2->item(r2)->setBackground(br);
                r2+=1;
                std::cerr<<"add2 :"<<r2<<std::endl;
            }
            for(int i=c1;i<n;i++){
                QString to1=QString::fromStdString(std::to_string(r1+1)+"  "+l1[c1]);
                ui->w1->insertItem(r1,to1);
                ui->w1->item(r1)->setForeground(QColor("red"));
                r1+=1;
                c1+=1;
            }
        }
        else{
            QString to1=QString::fromStdString(std::to_string(r1+1)+"  "+l1[c1]);
            ui->w1->insertItem(r1,to1);
            ui->w1->item(r1)->setForeground(QColor("red"));
            r1+=1;
            c1+=1;

            QString to2=QString::fromStdString(std::to_string(r2+1)+"  "+l2[c2]);
            ui->w2->insertItem(r2,to2);
            ui->w2->item(r2)->setForeground(QColor("red"));
            r2+=1;
            c2+=1;
        }
    }
    while(c1 < cnt1){
        QString to1=QString::fromStdString(std::to_string(r1+1)+"  "+l1[c1]);
        ui->w1->insertItem(r1,to1);
        ui->w1->item(r1)->setForeground(QColor("red"));
        r1+=1;
        c1+=1;
    }
    while(c2 < cnt2){
        QString to2=QString::fromStdString(std::to_string(r2+1)+"  "+l2[c2]);
        ui->w2->insertItem(r2,to2);
        ui->w2->item(r2)->setForeground(QColor("red"));
        r2+=1;
        c2+=1;
    }
}

int ComparePage::findnxt_same(std::string cur,std::string l2[70],int r2,int r2max){
    for(int i=r2;i<r2max;i++){
        if(cur.compare(l2[i])==0) return i;
    }
    return -1;
}

void ComparePage::read_same(){
    std::ifstream f;
    f.open("/Users/cc/Desktop/need_human.txt", std::ios::in);
    f>>cnt_same;
    for(int i=0;i<cnt_same;i++){
        f>>same[i][0];
        f>>same[i][1];
        f>>same[i][2];
        f>>same[i][3];
    }
    f.close();
}


void ComparePage::on_Equal_clicked()
{
    human_re[now]=1;
    this->Show_();
}


void ComparePage::on_Inequal_clicked()
{
    human_re[now]=2;
    this->Show_();
}


void ComparePage::on_Doubtful_clicked()
{
    human_re[now]=3;
    this->Show_();
}


void ComparePage::on_Before_clicked()
{
    now-=1;
//    ui->Num->setText(QString::number(now+1));
//    ui->File1->setText(QString::fromStdString(same[now][2]));
//    ui->File2->setText(QString::fromStdString(same[now][3]));
    this->Show_();
    this->show_txt();
}


void ComparePage::on_Next_clicked()
{
    now+=1;
//    ui->Num->setText(QString::number(now+1));
//    ui->File1->setText(QString::fromStdString(same[now][2]));
//    ui->File2->setText(QString::fromStdString(same[now][3]));
    this->Show_();
    this->show_txt();
}

