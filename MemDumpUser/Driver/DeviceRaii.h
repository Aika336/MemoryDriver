#pragma once
#include <Windows.h>

#define DeviceSymbolicName L"\\\\.\\MemReader"

struct DeviceRaii {
    DeviceRaii();
    ~DeviceRaii();

    HANDLE hDevice;
};