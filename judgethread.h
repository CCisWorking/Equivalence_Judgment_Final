#ifndef JUDGETHREAD_H
#define JUDGETHREAD_H

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <stdlib.h>
#include <math.h>

class JudgeThread
{
public:
    JudgeThread(std::string folderpath_,std::string folders_[20],int folders_cnt_,std::string files_[20][20],
                std::string files_path_[20][20],std::string files_name_[20][20],int folders_files_cnt_[20]);
    void Scan_Input(int idx);
    int Judge(int folder,int file1,int file2);

private:
    std::string folderpath;
    std::string folders[20];
    int folders_cnt;
    std::string files[20][20];
    std::string files_path[20][20];
    int folders_files_cnt[20];
    int paras[20][20]; // 0:char 1:int 2:string
    int paras_left[20][20];
    int paras_right[20][20];
    int paras_cnt[20];
    void InputFile(std::string x,std::string path);
    void recurse_input(int panum,int folder,int file,std::string after,std::string path,std::string order1,std::string order2);
    std::string letter[52];
    std::string getstr(int len,int cnt);
    std::string same[30][4];
    int cnt_same=0;

};

#endif // JUDGETHREAD_H
