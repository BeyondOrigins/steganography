#include "stdafx.h"

#include "encrypt.h"

using namespace std;

namespace enc {
    DLLEXPORT int __stdcall encrypt(string key_path, string data_path, string result_path) noexcept {
        ofstream file(result_path);
        file << "";
        file.close();
        string key_filetype    = key_path.substr(key_path.find_last_of('.') + 1);
        string result_filetype = result_path.substr(result_path.find_last_of('.') + 1);
        if (key_filetype == result_filetype) {
            // temporary
            FileData* key = new ImageData();
            FileData* data = new TextData();
            bool KEY_FLAG = key->rdff(key_path.c_str());
            bool DATA_FLAG = data->rdff(data_path.c_str());      
            if (!(KEY_FLAG && DATA_FLAG)) return 0;
            key->PrintInfo();
            // implementation of encryption algorythm
            vector<char> buf = key->GetData();
            vector<char> data_vector = data->GetData();
            size_t data_length = data_vector.size();
            size_t key_length = buf.size();

            for (size_t i = 0; i < data_length; ++i)
            {
                buf[i] = data_vector[i];
            }
            key->SetData(buf);
            int ok = key->wdtf(result_path.c_str());
            buf.clear();
            data_vector.clear();

            delete data, key;
            return ok;
        }
        else return 0;
    }
}
