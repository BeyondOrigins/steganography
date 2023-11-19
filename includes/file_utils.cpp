#include <iostream>

#include <fstream>
#include "file_utils.h"

using namespace std;

namespace stg {
  size_t FileData::GetFileLength(ifstream& file) {
    file.exceptions(fstream::badbit | fstream::failbit);
    size_t length = 0;
    try {
      file.seekg(0, ios::end);
      length = file.tellg();
      file.seekg(0, ios::beg);
    }
    catch (std::exception& ex) {
      cout << "Failed to get file length:\n:";
      cout << ex.what() << endl;
    }
    return length;
  }

  FileData::FileData() {}
  FileData::FileData (ifstream& file) { // constructor
    this->rdff(file);
  }

  void FileData::wdtf(ofstream& file) { // write data to file
    file.exceptions(fstream::badbit | fstream::failbit);
    try {
      cout << "Trying to write data into the file...\n";
      file.write(this->buf, this->length % 18000000);
      cout << "Success!\n";
    }

    catch (const exception& ex) {
      cout << "Failed to write data into the file:\n";
      cout << ex.what() << endl;
    }
  }

  void FileData::rdff(ifstream& file) { // read data from file
    this->length = GetFileLength(file);
    free(this->buf);
    this->buf = (char*)malloc(this->length * sizeof(char));
    try {
      cout << "Trying to read data from the file...\n";
      file.read(this->buf, this->length);
      cout << "Success!\n";
    }
    catch(exception& ex) {
      cout << "Failed to read data from file:\n";
      cout << ex.what() << endl;
    }
  }

  FileData::~FileData() { // destructor
    free(this->buf);
    cout << "FileData object deleted";
  }
}