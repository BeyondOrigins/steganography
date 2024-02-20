#include "includes/stdafx.h"

#include "includes/encrypt.h"
#include "includes/file_utils.h"

using namespace std;
using namespace enc;

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "ru");
    const char *mode = argv[1];
    if (strcmp(mode, "encrypt"))
    {
        const char *key_path = argv[2];
        const char *data_path = argv[3];
        const char *result_path = argv[4];
        int ok = encrypt(key_path, data_path, result_path);
        if (ok)
            cout << "COMPLITED\n";
        else
            cout << "FAILED\n";
    }
    else if (strcmp(mode, "decrypt"))
    {
        const char *enc_path = argv[2];
        const char *result_path = argv[3];
        int amount = -1;
        if (argc == 5)
        {
            amount = stoi(argv[4]);
        }
        int ok = decrypt(enc_path, result_path, amount);
        if (ok)
            cout << "COMPLITED\n";
        else
            cout << "FAILED\n";
    }
    else
    {
        cout << "UNKNOWN OPERATION\n";
    }
}