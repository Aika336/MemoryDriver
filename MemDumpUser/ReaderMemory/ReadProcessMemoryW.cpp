#include "../ReaderMemory/ReadProcessMemoryW.h"
#include "../Driver/DeviceRaii.h"
#include "../Driver/IoCtlCodes.h"
#include "../Driver/Requests.h"

#include <stdexcept>
#include <string>
#include <ntstatus.h>

#include <iostream>

NTSTATUS ReadProcessMemoryW(const char* targetName, LPVOID address, LPVOID outBuffer, int size) {
	if (!address || !outBuffer || size < 0 || strlen(targetName) > 15) {
		return STATUS_INVALID_PARAMETER;
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

	if (!state) {
		return STATUS_FATAL_APP_EXIT;
	}
	// Add check for a returned size
	
	return STATUS_SUCCESS;
}

NTSTATUS ReadProcessMemoryW(int pId, LPVOID address, LPVOID outBuffer, int size) {
	if (!address || !outBuffer || size < 0) {
		return STATUS_INVALID_PARAMETER;
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
	if (!state) {
		return STATUS_FATAL_APP_EXIT;
	}

	return STATUS_SUCCESS;
}