#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_
#include <iostream>
#include <fstream>
using namespace std;

namespace stfuncs {
    class FileData { // class to store file data
    private:
        char buf1[1800000];
        char buf2[1800000];
        inline size_t _get_file_length(ifstream& file) {}
    public:
        FileData () {}
        FileData (ifstream& file) {}
        void write(ofstream&) {}
    };
}

#endif