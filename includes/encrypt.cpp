#include "stdafx.h"

#include "encrypt.h"

using namespace std;

namespace enc
{
    __declspec(dllexport) int __stdcall encrypt(string key_path, string data_path, string result_path) noexcept
    {
        ofstream file(result_path);
        file << "";
        file.close();
        string key_filetype = key_path.substr(key_path.find_last_of('.') + 1);
        string result_filetype = result_path.substr(result_path.find_last_of('.') + 1);
        if (key_filetype == result_filetype)
        {
            FileData *key;
            FileData *data;
            FileData::CreateObject(key_path, key);
            FileData::CreateObject(data_path, data);
            if (!(key && data))
                return 0;
            key->PrintInfo();

            // implementation of the encryption algorythm
            vector<char> data_buf = data->GetData();
            vector<char> key_buf = key->GetData();
            int size = data_buf.size() * 8;
            for (int i = 0; i < size; ++i)
            {
                bool bit = (data_buf[i / 8] >> (i % 8)) & 1;
                key_buf[i] &= 0b11111110;
                key_buf[i] |= bit;
            }
            key->SetData(key_buf);
            int ok = key->wdtf(result_path.c_str());
            delete data, key;
            return ok;
        }
        else
            return 1;
    }

    __declspec(dllexport) int __stdcall decrypt(string enc_path, string result_path = "result.txt") noexcept
    {
        ofstream file(result_path);
        file << "";
        file.close();
        string enc_filetype = enc_path.substr(enc_path.find_last_of('.') + 1);
        FileData *enc;
        FileData *res;
        FileData::CreateObject(enc_path, enc);
        FileData::CreateObject(result_path, res);
        vector<char> enc_data = enc->GetData();
        if (!enc)
            return 0;
        char ch = 0;
        int idx = 0;
        vector<char> result_data;
        for (int i = 0; i < enc_data.size(); ++i)
        {
            ch = (ch << 1) | ((enc_data[i] & 1));
            ++idx;
            if (idx == 8)
            {
                idx = 0;
                ch = reverse(ch);
                result_data.push_back(ch);
                ch = 0;
            }
        }
        for (int i = 0; i < 5; ++i) {
            cout << result_data[i];
        }
        cout << endl;
        res->SetData(result_data);
        res->PrintInfo();
        int ok = res->wdtf(result_path.c_str());
        delete enc, res;
        return ok;
    }
}
