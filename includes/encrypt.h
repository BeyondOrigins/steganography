#ifndef ENCRYPT_H_
#define ENCRYPT_H_
#include <fstream>
#include <iostream>
#include <string>
#include "file_utils.h"

using namespace std;

namespace stfuncs {
    ofstream encrypt(char*, char*, FileData&);
}
#endif