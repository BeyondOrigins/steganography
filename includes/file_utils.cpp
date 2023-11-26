#include "stdafx.h"

#include "file_utils.h"

using namespace std;

namespace enc {
    size_t FileData::GetFileLength(ifstream& file) {
        file.exceptions(fstream::badbit | fstream::failbit);
        size_t length = 0;
        try {
            file.seekg(0, ios::end);
            length = file.tellg();
            file.seekg(0, ios::beg);
        }
        catch (std::exception& ex) {
            cout << "Failed to get file length";
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
            char* buf = (char*)malloc(sizeof(char) * this->_length);
            for (size_t i = 0; i < this->_length; i++)
            {
                buf[i] = this->_buf[i];
            }
            file.write(buf, this->_length);
            delete buf;
            cout << "Success!\n";
        }

        catch (const exception& ex) {
            cout << "Failed to write data into the file:\n";
            cout << ex.what() << endl;
        }
    }

    void FileData::rdff(ifstream& file) { // read data from file
        this->_length = GetFileLength(file);
        this->_buf.clear();
        try {
            // ДОДЕЛАТЬ
            cout << "Trying to read data from the file...\n";
            char ch;
            size_t counter = 0;
            while (file.get(ch)) {
                this->_buf.push_back(ch);
            }

            cout << "Success!\n";
        }
        catch(exception& ex) {}
    }

    FileData::~FileData() { // destructor
        cout << "FileData object deleted";
    }
}