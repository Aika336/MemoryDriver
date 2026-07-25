#include "../ReaderMemory/ReadProcessMemoryW.h"
#include "../Driver/DeviceRaii.h"
#include "../Driver/IoCtlCodes.h"
#include "../Driver/Requests.h"

#include <stdexcept>
#include <string>
#include <ntstatus.h>

bool ReadProcessMemoryW(const char* targetName, LPVOID address, LPVOID outBuffer, int size) {
	if (!address || !outBuffer || size < 0 || strlen(targetName) > 15) {
		throw std::invalid_argument("Invalid parameters passed to ReadProcessMemoryW");
	}
	
	DeviceRaii device;

	READ_REQUEST request{ (char*)targetName, NULL, (ULONG_PTR)address, size};

	DWORD bytesRet;

	BOOL state = DeviceIoControl(
		device.hDevice,
		IOCTL_READ_MEMORY_BY_NAME,
		&request, sizeof(request),
		outBuffer, size,
		&bytesRet,
		NULL
	);

	// Add check for a returned size
	
	return state;
}

bool ReadProcessMemoryW(int pId, LPVOID address, LPVOID outBuffer, int size) {
	if (!address || !outBuffer || size < 0) {
		throw std::invalid_argument("Invalid parameters passed to ReadProcessMemoryW");
	}

	DeviceRaii device;

	READ_REQUEST request{ NULL, pId, (ULONG_PTR)address, size };
	DWORD bytesRet = 0;

	BOOL state = DeviceIoControl(
		device.hDevice,
		IOCTL_READ_MEMORY_BY_HANDLE,
		&request, sizeof(request),
		outBuffer, size,
		&bytesRet,
		NULL
	);

	return state;
}