#include "includes/stdafx.h"

#include "includes/encrypt.h"
#include "includes/file_utils.h"

using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    char key_path[120] = "files\\SMART.jpg";
    char data_path[120] = "files\\file.txt";
    char buf_path[120] = "files\\file1.txt";
    ifstream file;
    ofstream ofile;
    ofile.open(buf_path, ios::out);
    file.open(data_path); 
    size_t length = enc::FileData::GetFileLength(file);
    enc::FileData* file_ = new enc::FileData();
    file_->rdff(file);
    file_->wdtf(ofile);
}