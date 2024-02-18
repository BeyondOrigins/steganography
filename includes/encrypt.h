#ifndef ENCRYPT_H_
#define ENCRYPT_H_

#include "stdafx.h"
#include "file_utils.h"

using namespace std;

namespace enc {
    DLLEXPORT int __stdcall encrypt(string, string, string) noexcept;
}
#endif  // ENCRYPT_H_