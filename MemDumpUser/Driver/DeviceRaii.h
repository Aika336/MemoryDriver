#pragma once
#include <Windows.h>

#define DeviceSymbolicName L"\\\\.\\MemReader"

struct DeviceRaii {
    DeviceRaii();
    DeviceRaii(DWORD desiredAccess);
    ~DeviceRaii();

    HANDLE hDevice;
};