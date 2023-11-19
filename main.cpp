#include <iostream>
#include <fstream>

#include <string>

#include "includes/encrypt.h"
#include "includes/file_utils.h"

using namespace std;

int main(int argc, char** argv) {
  setlocale(LC_ALL, "ru");
  char key_path[120] = "files\\SMART.jpg";
  char data_path[120] = "files\\file.txt";
  ifstream file;
  file.open(data_path); 
  size_t length = stg::FileData::GetFileLength(file);
  char* buf = (char*)malloc(sizeof(char) * length);
  stg::FileData* file_ = new stg::FileData();
  file_->rdff(file);
}