#include "includes/stdafx.h"

#include "includes/encrypt.h"
#include "includes/file_utils.h"

using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    char key_path[120] = "files\\SMART.jpg";
    char data_path[120] = "files\\file.txt";
    char buf_path[120] = "files\\file1.txt";
    
    enc::FileData* file_ = new enc::TextData();
    file_->rdff(data_path);
    file_->wdtf(buf_path);
    file_->PrintData();
}