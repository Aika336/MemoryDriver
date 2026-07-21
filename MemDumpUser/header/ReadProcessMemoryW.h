#include "DeviceRaii.h"
#include "IoCtlCodes.h"
#include "Requests.h"

NTSTATUS ReadProcessMemoryW(const char* targetName, LPVOID address, LPVOID outBuffer, int size);
NTSTATUS ReadProcessMemoryW(int pId, LPVOID address, LPVOID outBuffer, int size);