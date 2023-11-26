#ifndef ENCRYPT_H_
#define ENCRYPT_H_

#include "stdafx.h"

#include "file_utils.h"


using namespace std;

namespace enc {
    DLLEXPORT fstream encrypt(char*, char*, FileData&);
}
#endif  // ENCRYPT_H_