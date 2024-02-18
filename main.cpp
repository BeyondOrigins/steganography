#include "includes/stdafx.h"

#include "includes/encrypt.h"
#include "includes/file_utils.h"

using namespace std;
using namespace enc;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    char key[120] = "files\\SMART.png";
    char data[120] = "files\\file.txt";
    char result[120] = "files\\SMART1.png";
    int ok = encrypt(key, data, result);
    if (ok) cout << "Ok\n";
    else cout << "Error\n";
}