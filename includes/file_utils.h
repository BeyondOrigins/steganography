#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include "stdafx.h"

using namespace std;

namespace enc
{
    class FileData
    { // abstract data container class
    public:
        static int CreateObject(string, FileData *&);

        virtual int wdtf(const char *) noexcept = 0;
        virtual int rdff(const char *) noexcept = 0;

        vector<char> GetData() noexcept;
        void SetData(vector<char> &);

#ifdef DEVELOPE_MODE
        virtual void PrintData() = 0;
        virtual void PrintInfo() = 0;
#endif
        ~FileData();

    protected:
        vector<char> _buf;
        size_t _length;
    };

    class TextData : public FileData
    { // class to contain text files data
    public:
        explicit TextData();
        explicit TextData(const char *);

        int rdff(const char *) noexcept override;
        int wdtf(const char *) noexcept override;

#ifdef DEVELOPE_MODE
        void PrintData() override;
        void PrintInfo() override;
#endif
        ~TextData();
    };

    class ImageData : public FileData
    { // class to contain image files data
    public:
        explicit ImageData();
        explicit ImageData(const char *);

        int rdff(const char *) noexcept override;
        int wdtf(const char *) noexcept override;

#ifdef DEVELOPE_MODE
        void PrintData() override;
        void PrintInfo() override;
#endif
        ~ImageData();

    private:
        int _height;
        int _width;
        int _bpc = 8;
        int _comp = 3;
    };
    char reverse(char b);
}

#endif // FILE_UTILS_H_