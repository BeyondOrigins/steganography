#ifndef ENCRYPT_H_
#define ENCRYPT_H_

#include "stdafx.h"
#include "file_utils.h"

using namespace std;

namespace enc {
    __declspec(dllexport) int __stdcall encrypt(string, string, string) noexcept;
    __declspec(dllexport) int __stdcall decrypt(string, string, int) noexcept;
}
#endif  // ENCRYPT_H_