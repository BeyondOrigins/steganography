#include "stdafx.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "file_utils.h"
#include "stb_image.h"
#include "stb_image_write.h"

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
            cout << "Trying to write data into the text file...\n";
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
            cout << "Failed to write data into the text file:\n";
            cout << ex.what() << endl;
        }
    }

    void TextData::rdff(char* path) { // read data from file
        ifstream file;
        file.open(path);
        this->_buf.clear();
        cout << "Trying to read data from the text file...\n";
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

    TextData::~TextData() {
        cout << "TextData object deleted";
    }

    ImageData::ImageData() {}

    void ImageData::rdff(char* path) {
        ifstream file;
        file.open(path);
        int x, y, n, ok;
        ok = stbi_info(path, &x, &y, &n);
        this->_length = x * y * n;
        if (ok) {
            cout << "Trying to read data from the image...\n";
            uint8_t* rgb_image;
            try {
                rgb_image = stbi_load(path, &this->_width, &this->_height, &this->_bpp, 3);
                this->_buf.clear();
                for (size_t i = 0; i < this->_length; i++)
                {
                    this->_buf.push_back(static_cast<char>(rgb_image[i]));
                }
                cout << "Success!\n";
            }
        
            catch(exception& ex) {
                cout << "Failed to read data from the image:\n";
                cout << ex.what() << endl;
            }
            stbi_image_free(rgb_image);
        }
        else {
            cout << "Failed to read data from the image:\n";
            cout << "This file format is not supported\n";
        }
    }

    void ImageData::wdtf(char* path) {
        uint8_t* buf = (uint8_t*)malloc(sizeof(char) * this->_width * this->_height * 3);
        for (size_t i = 0; i < this->_length; i++)
        {
            buf[i] = static_cast<uint8_t>(this->_buf[i]);
        }
        stbi_write_png(path, this->_width, this->_height, 3, buf, this->_width * 3);
        delete buf;
    }

    ImageData::~ImageData() {
        cout << "ImageData object deleted\n";
    }
#ifdef DEVELOPE_MODE
    void TextData::PrintData() {
        for (size_t i = 0; i < this->_length; i++)
        {
            cout << this->_buf[i];
        }
    }

    void TextData::PrintInfo() {
        cout << "Data size: " << this->_length << endl;
        cout << "\r\n";
    }

    void ImageData::PrintData() {
        for (size_t i = 0; i < this->_length; i++)
        {
            cout << (int)this->_buf[i] << " ";
        }
    }

    void ImageData::PrintInfo() {
        cout << "Image width: " << this->_width << endl;
        cout << "Image height: " << this->_height << endl;
        cout << "Total data size: " << this->_length << endl;
        cout << "\r\n";
    }
#endif
}