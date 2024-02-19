#include "stdafx.h"

#include "encrypt.h"

using namespace std;

namespace enc {
    __declspec(dllexport) int __stdcall encrypt(string key_path, string data_path, string result_path) noexcept {
        ofstream file(result_path);
        file << "";
        file.close();
        string key_filetype    = key_path.substr(key_path.find_last_of('.') + 1);
        string result_filetype = result_path.substr(result_path.find_last_of('.') + 1);
        if (key_filetype == result_filetype) {
            FileData* key;
            FileData* data;
            FileData::CreateObject(key_path, key);
            FileData::CreateObject(data_path, data);
            if (!(key && data)) return 0;
            key->PrintInfo();

            // implementation of encryption the algorythm
            vector<char> data_buf = data->GetData();
            vector<char> key_buf = key->GetData();
            for (int i = 0; i < data_buf.size() * 8; i+=8) {
                char ch = data_buf[i / 8];
                for (int j = 0; j < 8; ++j) {
                    key_buf[i+j] |= (ch >> j) & 1;
                }
            }
            key->SetData(key_buf);
            int ok = key->wdtf(result_path.c_str());
            delete data, key;
            return ok;
        }
        else return 1;
    }

    __declspec(dllexport) int __stdcall decrypt(string key_path, string data_path, string result_path) noexcept {
        return 0;
    }
}
