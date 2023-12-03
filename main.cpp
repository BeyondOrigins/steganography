#include "includes/stdafx.h"

#include "includes/encrypt.h"
#include "includes/file_utils.h"

#include "includes/stb_image.h"

using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    char txt_path1[120] = "files\\file.txt";
    char txt_path2[120] = "files\\file1.txt";

    char png_path1[120] = "files\\SMART.png";
    char png_path2[120] = "files\\SMART1.png";
    enc::FileData* file = new enc::ImageData();
    file->rdff(png_path1);
    file->PrintInfo();
    file->wdtf(png_path2);
}