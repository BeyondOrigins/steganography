#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_
#include <iostream>
#include <fstream>
using namespace std;

namespace stg {
  class FileData { // class to store file data
  private:
    char* buf;
    size_t length;
  public:
    static size_t GetFileLength(ifstream&);
    explicit FileData ();
    FileData& operator=(const FileData& other) = default;
    explicit FileData (ifstream& file);
    void wdtf(ofstream&);
    void rdff(ifstream&);
    ~FileData();
  };
}

#endif  // FILE_UTILS_H_