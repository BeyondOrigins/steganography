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
            file.write(this->_buf, this->_length % 18000000);
            cout << "Success!\n";
        }

        catch (const exception& ex) {
            cout << "Failed to write data into the file:\n";
            cout << ex.what() << endl;
        }
    }

    void FileData::rdff(ifstream& file) { // read data from file
        this->_length = GetFileLength(file);
        free(this->_buf);
        this->_buf = (char*)malloc(this->_length * sizeof(char));
        try {
            cout << "Trying to read data from the file...\n";
            char   ch;
            size_t counter = 0;
            while (file.get(ch)) {
                this->_buf[counter] = ch;
                cout << (int)this->_buf[counter] << " ";
            }

            cout << "Success!\n";
        }
        catch(exception& ex) {
            cout << "Failed to read data from the file:\n";
            cout << ex.what() << endl;
        }
    }

    void FileData::print() {
        if (this->_length == 0) cout << "No data contained\r\n";
        else {
            for (size_t i = 0; i < this->_length; i++)
            {
                cout << this->_buf[i];
            }
            
        }
    }

    FileData::~FileData() { // destructor
        free(this->_buf);
        cout << "FileData object deleted";
    }
}