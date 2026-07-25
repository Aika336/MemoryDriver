#include "DeviceRaii.h"

#include <stdexcept>
#include <string>

DeviceRaii::DeviceRaii(DWORD desiredAccess) {
	hDevice = CreateFileW(
		DeviceSymbolicName,
		desiredAccess,
		0, NULL, OPEN_EXISTING, 0, NULL
	);

	if (!hDevice) {
		throw std::runtime_error("CreaetFile failed: " + std::to_string(GetLastError()));
	}
}

DeviceRaii::DeviceRaii() {
	hDevice = CreateFileW(
		DeviceSymbolicName,
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL
	);

	if (!hDevice) {
		throw std::runtime_error("CreaetFile failed: " + std::to_string(GetLastError()));
	}
}

DeviceRaii::~DeviceRaii() {
	if (hDevice) {
		CloseHandle(hDevice);
	}
}