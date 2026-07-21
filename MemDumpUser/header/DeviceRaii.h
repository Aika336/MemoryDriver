#include <Windows.h>

#define DeviceSymbolicName L"\\.\MemReader"

struct DeviceRaii {
    DeviceRaii();
    ~DeviceRaii();

    static HANDLE hDevice;
};