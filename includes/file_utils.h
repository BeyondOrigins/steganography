#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include "stdafx.h"

using namespace std;

namespace enc {
    class FileData { // class to store file data
    private:
        BUFFER _buf;
        size_t _length;
    public:
        static size_t GetFileLength(ifstream&);
        explicit FileData ();
        FileData& operator=(const FileData& other) = default;
        explicit FileData (ifstream& file);
        void wdtf(ofstream&);
        void rdff(ifstream&);
        void print();
        ~FileData();
    };
}

#endif  // FILE_UTILS_H_