#include <iostream>
#include <fstream>
#include "file_utils.h"

using namespace std;

namespace stfuncs {
    class FileData {
    private:
        char buf1[1800000];
        char buf2[1800000];
        int length;
        inline size_t _get_file_length(ifstream& file) {
            file.exceptions(fstream::badbit | fstream::failbit);
            size_t length;
            try {
                file.seekg(0, ios::end);
                length = file.tellg();
                file.seekg(0, ios::beg);
            }
            catch (std::exception& ex) {
                cout << "File need to be opened\n";
            }
            return length;
        }
    public:
        FileData() {}
        FileData (ifstream& file) { // constructor
            size_t length_ = _get_file_length(file);
            this->length = length_;
            size_t addit_length;
            if (length_ > 1800000) {
                addit_length = length_ - 1800000 > 1800000 ? 1800000 : length_ - 1800000;
                length_ = 1800000;
            }
            file.read(this->buf1, length_);
            if (addit_length > 0) {
                file.seekg(length_);
                file.read(this->buf2, length_);
            }
        }

        void write(ofstream& file) { // write data contained by this object into a file
            file.exceptions(fstream::badbit | fstream::failbit);
            try {
                cout << "Attempt to write data into file...\n";
                file.write(this->buf1, this->length % 18000000);
                if (this->length - 18000000 > 0) 
                    file.write(this->buf2, this->length - 18000000);
                cout << "Success!\n";
            }

            catch (const exception& ex) {
                cout << "Failed to write data into a file:\n";
                cout << ex.what() << endl;
            }
        }
    };
}