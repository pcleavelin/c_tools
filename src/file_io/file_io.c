#if defined(__unix__) || defined(__APPLE__)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

unsigned long get_file_size(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    assert(file && "get_file_size: failed to open file");

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    fclose(file);

    return fsize;
}

bool load_file(const char *filePath, unsigned long size, void *buffer) {
    FILE *file = fopen(filePath, "r");
    assert(file && "load_file: failed to open file");

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    fread(buffer, fsize, 1, file);

    fclose(file);

    return true;
}

#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#define assertm(exp, msg) assert(((void)msg, exp))

VOID CALLBACK FileIOCompletionRoutine(
        __in  DWORD dwErrorCode,
        __in  DWORD dwNumberOfBytesTransfered,
        __in  LPOVERLAPPED lpOverlapped )
{
    printf("Error code: %li", dwErrorCode);
    printf("Number of bytes: %li", dwNumberOfBytesTransfered);
}

unsigned long get_file_size(const char *filePath) {
    HANDLE hFile = CreateFile(filePath,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            NULL);

    LARGE_INTEGER size;
    assert(GetFileSizeEx(hFile, &size) && "get_file_size: failed to get file size");

    return size.LowPart;
}

bool load_file(const char *filePath, unsigned long size, void *buffer) {
    HANDLE hFile = CreateFile(filePath,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    OVERLAPPED ol = {0};
    unsigned long bytesRead = 0;
    if (!ReadFile(hFile, buffer, size, &bytesRead, NULL)) {
        unsigned long error = GetLastError();
        unsigned long msg = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buffer, size, NULL);

        printf("failed to load file: %s\n", (char *)buffer);
        assert(false && "failed to read file");
    }
    assert(bytesRead == size && "load_file: didn't one-shot read the whole file");

    return true;
}
#endif
