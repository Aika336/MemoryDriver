#include "WriteProcessMemory.h"

#include "../Driver/DeviceRaii.h"
#include "../Driver/IoCtlCodes.h"
#include "../Driver/Requests.h"

#include <ntstatus.h>

NTSTATUS WriteProcessMemoryW(const char* targetName, LPVOID targetAddress, LPVOID dataBuffer, int size) {
	if (!targetName || !targetAddress || size < 0 || strlen(targetName) > 15) {
		return STATUS_INVALID_PARAMETER;
	}

	DeviceRaii device;

	WRITE_REQUEST request{(char*)targetName , NULL, (ULONG_PTR)targetAddress, (ULONG_PTR)dataBuffer, size};

	DWORD bytesRet;

	BOOL state = DeviceIoControl(
		device.hDevice,
		IOCTL_READ_MEMORY_BY_NAME,
		&request, sizeof(request),
		NULL, 0,
		&bytesRet,
		NULL
	);

	if (!state) {
		return STATUS_FATAL_APP_EXIT;
	}

	return STATUS_SUCCESS;
}

NTSTATUS WriteProcessMemoryW(ULONG processId, LPVOID targetAddress, LPVOID dataBuffer, int size) {
	if (!targetAddress || size < 0) {
		return STATUS_INVALID_PARAMETER;
	}

	DeviceRaii device;

	WRITE_REQUEST request{ NULL , processId, (ULONG_PTR)targetAddress, (ULONG_PTR)dataBuffer, size };

	DWORD bytesRet;

	BOOL state = DeviceIoControl(
		device.hDevice,
		IOCTL_READ_MEMORY_BY_NAME,
		&request, sizeof(request),
		NULL, 0,
		&bytesRet,
		NULL
	);

	if (!state) {
		return STATUS_FATAL_APP_EXIT;
	}

	return STATUS_SUCCESS;
}