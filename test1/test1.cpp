#include <iostream>
#include <windows.h>

int main()
{
    std::wcout << L"Project --> Offline file signature scanner & Hex Utility <--\n";
    std::wcout << L"Opening the file...\n";

    HANDLE hFile = CreateFileW(
        L"example.txt",
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::wcout << L"Failed to open file. Error: "
            << GetLastError() << std::endl;
        return 1;
    }

    std::wcout << L"File opened successfully!\n";

    // STEP 1: Get file size
    LARGE_INTEGER size;

    if (!GetFileSizeEx(hFile, &size)) {
        std::wcout << L"Failed to get file size. Error: "
            << GetLastError() << std::endl;

        CloseHandle(hFile);
        return 1;
    }

    std::wcout << L"File size: "
        << size.QuadPart
        << L" bytes\n";

    // STEP 2: Allocate memory
    unsigned char* fileBuffer =
        new unsigned char[(size_t)size.QuadPart];

    DWORD bytesRead = 0;

    // STEP 3: Read file
    if (ReadFile(
        hFile,
        fileBuffer,
        (DWORD)size.QuadPart,
        &bytesRead,
        NULL))
    {
        std::wcout << L"File read successfully!\n";
        std::wcout << L"Bytes read: "
            << bytesRead << std::endl;

        // Example: printing the file bytes in hex
        std::wcout << L"\n reading the file :\n";

        for (DWORD i = 0; i < bytesRead && i < size.QuadPart; i++) {
            printf("%02X ", fileBuffer[i]);
        }
        std::wcout << L"\n reading the file with contents :\n";
        for (DWORD i = 0; i < bytesRead; i++) {
            printf("Byte %lu: %02X  '%c'\n",
                i,
                fileBuffer[i],
                fileBuffer[i]);
        }

        printf("\n");
    }
    else {
        std::wcout << L"Failed to read file. Error: "
            << GetLastError() << std::endl;
    }

    // Cleanup
    delete[] fileBuffer;
    CloseHandle(hFile);

    return 0;
}

