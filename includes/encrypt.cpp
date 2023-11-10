#include <fstream>
#include <iostream>
#include "encrypt.h"

#include <string>

using namespace std;

namespace stfuncs {
    inline size_t get_file_length(ifstream& file) {
        file.seekg(0, ios::end);
        size_t length = file.tellg();
        file.seekg(0, ios::beg);
        return length;
    }

    ofstream encrypt(char* key_path, char* data_path, FileData& result) {
        ifstream key, data;
        char key_buffer[100000];
        char data_buffer[100000];
        key.exceptions(fstream::badbit | fstream::failbit);

        try {
            cout << "Attempt to open the key file...\n";
            key.open(key_path, ios::in);
            cout << "Key file has been successfully opened\n";
            cout << "Attempt to open the data file...\n";
            data.open(data_path, ios::in);
            cout << "Data file has been successfully opened\n";
        }

        catch (const exception& ex) {
            cout << "\nFile opening error:\n";
            cout << endl <<ex.what() << endl;
        } 

        size_t key_length = get_file_length(key);
        size_t data_length = get_file_length(data);

        if (key_length > sizeof (key_buffer)) key_length = sizeof (key_buffer);
        if (data_length > sizeof(data_buffer)) data_length = sizeof(data_buffer);

        // key.read(key_buffer, key_length);
        data.read(data_buffer, data_length);
        for (size_t i = 0; i < data_length; i++)
        {
            cout << data_buffer[i] << endl;
        }
        return ofstream();
    }
}
