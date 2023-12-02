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
        this->_buf.clear();
        if (file.is_open()) {
            string str;
            while (!file.eof()) {
                getline(file, str);
                size_t temp_length = str.length();
                char* temp_buf = new char[temp_length + 1];
                strcpy(temp_buf, str.c_str());
                for (size_t i = 0; i < temp_length; i++)
                {
                    this->_buf.push_back(temp_buf[i]);
                }
                this->_buf.push_back('\n');
                delete temp_buf;
            }
            this->_length = this->_buf.size();
        }
    }

    FileData::~FileData() { // destructor
        cout << "FileData object deleted";
    }
}