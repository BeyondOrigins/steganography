// DOCUMENTATION
//
// int wdtf(const char* path) - Write Data To File
//     PARAMS:
//         *path - pointer to char string, that contains the file path that need to be read
//     RETURN:
//         on success 1 is returned, on error 0 is returned
//
// int rdff(const char* path) - Read Data From File
//     PARAMS:
//         *path - pointer to char string, that contains the file path where the data will be written
//     RETURN:
//         on success 1 is returned, on error 0 is returned

#include "stdafx.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8

#include "file_utils.h"
#include "stb_image.h"
#include "stb_image_write.h"

using namespace std;

namespace enc
{
    int FileData::CreateObject(string path, FileData *&obj)
    {
        string type = path.substr(path.find_last_of('.') + 1);
        if (type == "png" || type == "gif" || type == "pic" || type == "bmp" || type == "hdr")
        {
            obj = new ImageData(path.c_str());
            return 1;
        }
        else if (type == "txt" || type == "rtf")
        {
            obj = new TextData(path.c_str());
            return 1;
        }
        obj = nullptr;
        return 0;
    }

    vector<char> FileData::GetData() noexcept
    {
        return this->_buf;
    }

    void FileData::SetData(vector<char> &new_data)
    {
        this->_buf = new_data;
        this->_length = new_data.size();
    }

    FileData::~FileData()
    {
        this->_buf.clear();
        cout << "FileData object deleted\n";
    }

    TextData::TextData() {}

    TextData::TextData(const char *path) // constructor
    {
        this->rdff(path);
    }

    int TextData::wdtf(const char *path) noexcept // write data to file
    { 
        ofstream file;
        file.open(path, ios::out);
        file.exceptions(fstream::badbit | fstream::failbit);
        try
        {
            cout << "Trying to write data into the text file...\n";
            char *buf = (char *)malloc(sizeof(char) * this->_length);
            for (size_t i = 0; i < this->_length; i++)
            {
                buf[i] = this->_buf[i];
            }
            file.write(buf, this->_length);
            delete buf;
            cout << "Success!\n";
            return 1;
        }

        catch (const exception &ex)
        {
            cout << "Failed to write data into the text file:\n";
            cout << ex.what() << endl;
            return 0;
        }
    }

    int TextData::rdff(const char *path) noexcept // read data from file
    { 
        ifstream file;
        file.open(path);
        this->_buf.clear();
        cout << "Trying to read data from the text file...\n";
        try
        {
            string str;
            while (!file.eof())
            {
                getline(file, str);
                for (const char &c : str)
                {
                    this->_buf.push_back(c);
                }
                this->_buf.push_back('\n');
            }
            this->_buf.pop_back();
            this->_length = this->_buf.size();
            cout << "Success!\n";
            return 1;
        }
        catch (exception &ex)
        {
            cout << "Failed to read data from file:\n";
            cout << ex.what() << endl;
            return 0;
        }
    }

    TextData::~TextData()
    {
        cout << "TextData object deleted";
    }

    ImageData::ImageData() {}

    ImageData::ImageData(const char *path)
    {
        int result = this->rdff(path);
    }

    int ImageData::rdff(const char *path) noexcept
    {
        ifstream file;
        file.open(path);
        int ok = stbi_info(path, &this->_width, &this->_height, &this->_comp);

        if (ok)
        {
            this->_length = this->_width * this->_height * this->_comp;
            cout << "Trying to read data from the image...\n";
            uint8_t *rgba_image = stbi_load(path, &this->_width, &this->_height, &this->_bpc, this->_comp);
            this->_buf.clear();
            if (rgba_image)
            {
                for (size_t i = 0; i < this->_length; i++)
                {
                    this->_buf.push_back(static_cast<char>(rgba_image[i]));
                }
                cout << "Success!\n";
                stbi_image_free(rgba_image);
                return 1;
            }
            else
            {
                cout << "Failed to read data from the image:\n";
                cout << "Unknown error\n";
                return 0;
            }
        }
        else
        {
            cout << "Failed to read data from the image:\n";
            cout << "Unsupported image format\n";
            return 0;
        }
    }

    int ImageData::wdtf(const char *path) noexcept
    {
        uint8_t *buf = (uint8_t *)malloc(sizeof(char) * this->_width * this->_height * this->_bpc);
        for (size_t i = 0; i < this->_length; i++)
        {
            buf[i] = static_cast<uint8_t>(this->_buf[i]);
        }
        int result = stbi_write_png(path, this->_width, this->_height, this->_bpc, buf, this->_width * this->_bpc);
        delete buf;
        return result;
    }

    ImageData::~ImageData()
    {
        cout << "ImageData object deleted\n";
    }

    char reverse(char b)
    {
        b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
        b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
        b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
        return b;
    }

#ifdef DEVELOPE_MODE
    void TextData::PrintData()
    {
        for (size_t i = 0; i < this->_length; i++)
        {
            cout << this->_buf[i];
        }
    }

    void TextData::PrintInfo()
    {
        cout << "\r\n";
        cout << "Data size: " << this->_length << endl;
        cout << "\r\n";
    }

    void ImageData::PrintData()
    {
        for (size_t i = 0; i < this->_length; i++)
        {
            cout << (int)this->_buf[i] << " ";
        }
    }

    void ImageData::PrintInfo()
    {
        cout << "\r\n";
        cout << "Image width: " << this->_width << endl;
        cout << "Image height: " << this->_height << endl;
        cout << "Bits per component: " << this->_bpc << endl;
        cout << "Number of components per pixel: " << this->_comp << endl;
        cout << "Total data size: " << this->_length << endl;
        cout << "\r\n";
    }
#endif
}