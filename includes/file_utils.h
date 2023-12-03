#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include "stdafx.h"

using namespace std;

namespace enc {
    class FileData { // abstract data container class
    public:
        enum class FileType {
            kText = 0,
            kImage,
            kAudio
        };
        explicit FileData ();
        static size_t GetFileLength(ifstream&);
        
        virtual void wdtf(char*) = 0;
        virtual void rdff(char*) = 0;
        virtual void PrintData() = 0;
        ~FileData();
    protected:
        vector<char> _buf;
        size_t _length;
    };

    class TextData : public FileData {
    public:
        const FileType file_type = FileData::FileType::kText;
        void rdff(char*);
        void wdtf(char*);
        explicit TextData();
        explicit TextData(char*);
        void PrintData();
        ~TextData();
    };

    class ImageData : public FileData {
    public:
        const FileType file_type = FileData::FileType::kImage;
        void rdff(char*);
        void wdtf(ofstream& file);
        explicit ImageData();
        explicit ImageData(char*);
        void PrintData();
        ~ImageData();
    private:
        int  _height;
        int _width;
        int _bpp;
    };
}

#endif  // FILE_UTILS_H_