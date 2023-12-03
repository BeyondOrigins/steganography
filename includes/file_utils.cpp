#include "stdafx.h"

#include "file_utils.h"
#include "stb_image.h"

using namespace std;

namespace enc {
    FileData::FileData() {}

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

    FileData::~FileData() { // destructor
        cout << "FileData object deleted";
    }

    TextData::TextData() {}
    TextData::TextData (char* path) { // constructor
        this->rdff(path);
    }

    void TextData::wdtf(char* path) { // write data to file
        ofstream file;
        file.open(path, ios::out);
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

    void TextData::rdff(char* path) { // read data from file
        ifstream file;
        file.open(path);
        this->_buf.clear();
        cout << "Trying to read data from file...\n";
        try {
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
                this->_buf.pop_back();
                this->_length = this->_buf.size();
                cout << "Success!\n";
            }
            else {
                cout << "Failed to read data from file: file isn't opened\n";
            }
        }
        catch (exception& ex) {
            cout << "Failed to read data from file:\n";
            cout << ex.what() << endl;
        }  
    }

    void TextData::PrintData() {
        cout << "File length: " << this->_length << endl;
        for (size_t i = 0; i < this->_length; i++)
        {
            cout << this->_buf[i];
        }
    }

    TextData::~TextData() {
        cout << "TextData object deleted";
    }

    void ImageData::rdff(char* path) {
        uint8_t* rgb_image = stbi_load(path, &this->_width, &this->_height, &this->_bpp, 3);
        
        stbi_image_free(rgb_image);
    }
}