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
#ifdef DEVELOPE_MODE
        virtual void PrintData() = 0;
        virtual void PrintInfo() = 0;
#endif
        ~FileData();
    protected:
        vector<char> _buf;
        size_t _length;
    };

    class TextData : public FileData { // class to store text files data
    public:
        const FileType file_type = FileData::FileType::kText;
        void rdff(char*);
        void wdtf(char*);
        explicit TextData();
        explicit TextData(char*);
#ifdef DEVELOPE_MODE
        void PrintData();
        void PrintInfo();
#endif
        ~TextData();
    };

    class ImageData : public FileData { // class to store image files data
    public:
        const FileType file_type = FileData::FileType::kImage;
        void rdff(char*);
        void wdtf(char*);
        explicit ImageData();
        explicit ImageData(char*);
#ifdef DEVELOPE_MODE
        void PrintData();
        void PrintInfo();
#endif
        ~ImageData();
    private:
        int _height;
        int _width;
        int _bpp = 8;
    };
}

#endif  // FILE_UTILS_H_