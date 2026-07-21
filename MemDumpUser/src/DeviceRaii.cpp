#include "DeviceRaii.h"
#include <stdexcept>

DeviceRaii::DeviceRaii() {
	hDevice = CreateFileW(
		DeviceSymbolicName,
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL
	);

	if (!hDevice) {
		throw std::runtime_error("CreaetFile failed: " + GetLastError());
	}
}

DeviceRaii::~DeviceRaii() {

}