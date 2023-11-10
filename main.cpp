#include <iostream>
#include <fstream>

#include <string>

#include "includes/encrypt.h"
#include "includes/file_utils.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    ifstream file;
    char key_path[120] = "files\\SMART.jpg";
    char data_path[120] = "files\\file.txt";
    stfuncs::FileData result;
    stfuncs::encrypt(key_path, data_path, result);
}