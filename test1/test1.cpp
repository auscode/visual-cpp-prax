#include <iostream>
#include <windows.h>
int main()
{
    std::wcout << L"Project-->Offline file signature scanner & Hex Utility<--\n";
    std::wcout << L"Opening the file\n";
    HANDLE hFile = CreateFileW(
        L"example.txt",          // File name (wide string)
        GENERIC_READ,            // Desired access
        FILE_SHARE_READ,         // Share mode
        NULL,                    // Security attributes
        OPEN_EXISTING,           // Creation disposition
        FILE_ATTRIBUTE_NORMAL,   // Flags and attributes
        NULL                     // Template file
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        std::wcout << L"Failed to open file. Error: "
            << GetLastError() << std::endl;
        return 1;
    }
    std::wcout << L"File opened successfully!\n" << std::endl;
    std::wcout << L"Size of the File is " << std::endl;
    
    LARGE_INTEGER fileSize;
    if (GetFileSizeEx(hFile, &fileSize)) {
        std::cout << "File size: "
            << fileSize.QuadPart
            << " bytes\n";
    }
    else {
        std::cout << "Failed to get file size\n";
    }
    CloseHandle(hFile);
    return 0;   
}