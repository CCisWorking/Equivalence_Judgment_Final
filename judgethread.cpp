#include "judgethread.h"


JudgeThread::JudgeThread(std::string folderpath_,std::string folders_[20],int folders_cnt_,
                         std::string files_[20][20],std::string files_path_[20][20],std::string files_name_[20][20],int folders_files_cnt_[20])
{
    folderpath=folderpath_;
    folders_cnt=folders_cnt_;
    for(int i=0;i<folders_cnt_;i++) folders[i]=folders_[i];
    for(int i=0;i<folders_cnt;i++)folders_files_cnt[i]=folders_files_cnt_[i];
    for(int i=0;i<folders_cnt;i++)
        for(int j=0;j<folders_files_cnt[i];j++){
            files[i][j]=files_[i][j];
            files_path[i][j]=files_path_[i][j];
//            std::cerr<<"files[i][j]:"<<files[i][j]<<std::endl;
//            std::cerr<<"files_path[i][j]:"<<files_path[i][j]<<std::endl;
        }
    letter[0]="a";letter[1]="b";letter[2]="c";letter[3]="d";letter[4]="e";letter[5]="f";letter[6]="g";
    letter[7]="h";letter[8]="i";letter[9]="j";letter[10]="k";letter[11]="l";letter[12]="m";letter[13]="n";
    letter[14]="o";letter[15]="p";letter[16]="q";letter[17]="r";letter[18]="s";letter[19]="t";letter[20]="u";
    letter[21]="v";letter[22]="w";letter[23]="x";letter[24]="y";letter[25]="z";
    letter[26]="A";letter[27]="B";letter[28]="C";letter[29]="D";letter[30]="E";letter[31]="F";letter[32]="G";
    letter[33]="H";letter[34]="I";letter[35]="J";letter[36]="K";letter[37]="L";letter[38]="M";letter[39]="N";
    letter[40]="O";letter[41]="P";letter[42]="Q";letter[43]="R";letter[44]="S";letter[45]="T";letter[46]="U";
    letter[47]="V";letter[48]="W";letter[49]="X";letter[50]="Y";letter[51]="Z";
    for(int i=0;i<folders_cnt;i++) this->Scan_Input(i);
    std::cerr<<"f1:"<<files[0][0]<<std::endl;
    std::cerr<<"f2:"<<files[0][1]<<std::endl;
    std::ofstream eq;
    std::ofstream neq;
    eq.open("/Users/cc/Desktop/equal.csv", std::ios::out);
    neq.open("/Users/cc/Desktop/inequal.csv", std::ios::out);
    eq << "file1" << ',' << "file2" <<std::endl;
    neq << "file1" << ',' << "file2" <<std::endl;
    for(int i=0;i<folders_cnt;i++){
        for(int j=0;j<folders_files_cnt[i];j++){
            for(int k=j+1;k<folders_files_cnt[i];k++){
                int re=this->Judge(i,j,k);
                std::cerr<<re<<":    "<<files_path[i][j]<<" "<<files_path[i][k]<<std::endl;
                if(re == -1) continue;
                else re=!re;
                if(re) {
                    eq<<files_path[i][j]<<","<<files_path[i][k]<<std::endl;
                    same[cnt_same][0]=files[i][j];
                    same[cnt_same][1]=files[i][k];
                    same[cnt_same][2]=files_path[i][j];
                    same[cnt_same][3]=files_path[i][k];
                    cnt_same+=1;
                }
                else {
                    neq<<files_path[i][j]<<","<<files_path[i][k]<<std::endl;
                }
            }
        }
    }
    eq.close();
    neq.close();
    std::fstream f;
    f.open("/Users/cc/Desktop/need_human.txt",std::ios::out);
    f<<cnt_same<<"\n";
    for(int i=0;i<cnt_same;i++){
        f<<same[i][0]<<"\n";
        f<<same[i][1]<<"\n";
        f<<same[i][2]<<"\n";
        f<<same[i][3]<<"\n";
    }
    f.close();
}

void JudgeThread::Scan_Input(int idx){
    std::string path=folderpath+folders[idx]+"/stdin_format.txt";
//    std::cerr<<path<<std::endl;
    std::ifstream ifs(path);
    std::string str;
    int count = 0;
    while (ifs >> str)
    {
        std::regex char_reg("char{1}");
        std::regex int_reg("int((.*),(.*))");
        std::regex string_reg("string((.*),(.*))");
        std::smatch results;
        if(std::regex_match(str,char_reg)){
//            std::cerr<<"char!"<<std::endl;
            paras[idx][count]=0;
        }
        else if(std::regex_match(str,int_reg)){
//            std::cerr<<"int!"<<std::endl;
            std::string tmp(str);
            int x=tmp.find(",");
            int y=tmp.length();
            std::string left(str.substr(4,x-4));
            std::string right(str.substr(x+1,y-x-2));
            paras[idx][count]=1;
            paras_left[idx][count]=atoi(left.c_str());
            paras_right[idx][count]=atoi(right.c_str());
//            std::cerr<<atoi(left.c_str())<<" "<<atoi(right.c_str())<<std::endl;
        }
        else if(std::regex_match(str,string_reg)){
//            std::cerr<<"string!"<<std::endl;
            paras[idx][count]=2;
            std::string tmp(str);
            int x=tmp.find(",");
            int y=tmp.length();
            std::string left(str.substr(7,x-7));
            std::string right(str.substr(x+1,y-x-2));
            paras_left[idx][count]=atoi(left.c_str());
            paras_right[idx][count]=atoi(right.c_str());
//            std::cerr<<atoi(left.c_str())<<" "<<atoi(right.c_str())<<std::endl;
        }
//        std::cerr << str << std::endl;
        count++;
    }
    paras_cnt[idx]=count;
    ifs.close();
}

int JudgeThread::Judge(int folder,int file1,int file2){
    std::string f1p=files[folder][file1];
    std::string f2p=files[folder][file2];
    std::string order1="g++ -o "+f1p.substr(0,f1p.length()-4)+".out"+" "+f1p+">> /Users/cc/Desktop/oo.txt 2>&1";
    std::string order2="g++ -o "+f2p.substr(0,f2p.length()-4)+".out"+" "+f2p+">> /Users/cc/Desktop/oo.txt 2>&1";
    std::string outfile1=f1p.substr(0,f1p.length()-4);
    std::string outfile2=f2p.substr(0,f2p.length()-4);
    std::string order3=outfile1+".out  < "+folderpath+folders[folder]+"/"+"input.txt "+">>"+folderpath+folders[folder]+"/"+"output1.txt";
    std::string order4=outfile2+".out  < "+folderpath+folders[folder]+"/"+"input.txt "+">>"+folderpath+folders[folder]+"/"+"output2.txt";
    const char *_1=order1.c_str();
    const char *_2=order2.c_str();
    std::string order5="rm "+outfile1+".out";
    std::string order6="rm "+outfile2+".out";
    const char *_5=order5.c_str();
    const char *_6=order6.c_str();
    std::string inputfile_path(folderpath+"/"+folders[folder]+"/"+"input.txt");
    int t1=system(_1);
    if(t1 != 0 ) return -1;
    int t2=system(_2);
    if(t2 !=0 ) {
        system(_5);
        return -1;
    }
    this->recurse_input(paras_cnt[folder],folder,file1,"",inputfile_path,order3,order4);
    system(_5);
    system(_6);
    std::string order7="diff "+folderpath+folders[folder]+"/"+"output1.txt"+" "+folderpath+folders[folder]+"/"+"output2.txt > "
                        +folderpath+folders[folder]+"/"+"out.txt";
    const char *_7=order7.c_str();
    bool re=system(_7);
    std::string order8="rm "+folderpath+folders[folder]+"/"+"out.txt";
    const char *_8=order8.c_str();
    system(_8);
    std::string order9="rm "+folderpath+folders[folder]+"/"+"output1.txt";
    const char *_9=order9.c_str();
    system(_9);
    std::string order10="rm "+folderpath+folders[folder]+"/"+"output2.txt";
    const char *_10=order10.c_str();
    system(_10);
    std::string order11="rm "+folderpath+folders[folder]+"/"+"input.txt";
    const char *_11=order11.c_str();
    system(_11);
    return re;
}

void JudgeThread::InputFile(std::string x,std::string path){
    std::ofstream outfile;
    outfile.open(path, std::ios_base::out);
    outfile<<x;
    outfile.close();
}

void JudgeThread::recurse_input(int panum,int folder,int file,std::string after,std::string path,std::string order1,std::string order2){
    if(panum == 1){
        if(paras[folder][file]==0){
            for(int i=0;i<52;i++){
                std::string tmp(letter[i]+" "+after);
                this->InputFile(tmp,path);
                const char *_1=order1.c_str();
                const char *_2=order2.c_str();
//                std::cerr<<"input:"<<tmp<<std::endl;
//                std::cerr<<order1<<std::endl;
                system(_1);
//                std::cerr<<order2<<std::endl;
                system(_2);
            }
        }
        else if(paras[folder][file]==1){
            int left=paras_left[folder][file];
            int right=paras_right[folder][file];
            for(int i=left;i<=right;i++){
                std::string tmp(std::to_string(i)+" "+after);
                this->InputFile(tmp,path);
                const char *_1=order1.c_str();
                const char *_2=order2.c_str();
//                std::cerr<<"input:"<<tmp<<std::endl;
//                std::cerr<<order1<<std::endl;
                system(_1);
//                std::cerr<<"out1";
//                std::cerr<<order2<<std::endl;
                system(_2);
//                std::cerr<<"out2";
            }

        }
        else{
            int left=paras_left[folder][file];
            int right=paras_right[folder][file];
            for(int i=left;i<=right;i++){
                for(int j=0;j<=pow(52,i);j++){
                    std::string tmp(this->getstr(i,j)+" "+after);
                    this->InputFile(tmp,path);
                    const char *_1=order1.c_str();
                    const char *_2=order2.c_str();
//                    std::cerr<<"input:"<<tmp<<std::endl;
//                    std::cerr<<order1<<std::endl;
                    system(_1);
//                    std::cerr<<order2<<std::endl;
                    system(_2);
                }
            }
        }
    }
    else{
        if(paras[folder][file]==0){
            for(int i=0;i<52;i++){
                std::string tmp(letter[i]+" "+after);
                this->recurse_input(panum-1,folder,file,tmp,path,order1,order2);
            }
        }
        else if(paras[folder][file]==1){
            int left=paras_left[folder][file];
            int right=paras_right[folder][file];
            for(int i=left;i<=right;i++){
                std::string tmp(std::to_string(i)+" "+after);
                this->recurse_input(panum-1,folder,file,tmp,path,order1,order2);
            }
        }
        else{
            int left=paras_left[folder][file];
            int right=paras_right[folder][file];
            for(int i=left;i<=right;i++){
                for(int j=0;j<=pow(52,i);j++){
                    std::string tmp(this->getstr(i,j)+" "+after);
                    this->recurse_input(panum-1,folder,file,tmp,path,order1,order2);
                }
            }
        }
    }
//    std::cerr<<"out";
}

std::string JudgeThread::getstr(int len,int cnt){
    std::string tmp;
    int cnt_=0;
    while(cnt_<len){
        tmp=letter[cnt%52]+tmp;
        cnt=cnt/52;
        cnt_+=1;
    }
    return tmp;
}
