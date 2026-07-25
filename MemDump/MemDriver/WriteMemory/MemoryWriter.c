#include "MemoryWriter.h"
#include "../ProcessManager/ProcessFinder.h"

NTSTATUS NameWriteRequest(PCHAR targetName, PVOID address, PVOID writeData, ULONG size) {
	PEPROCESS process = FindProcessByName(targetName);

	if (!process) {
		return STATUS_NOT_FOUND;
	}

	SIZE_T bytesWritten = 0;
	NTSTATUS status = MmCopyVirtualMemory(
		PsGetCurrentProcess(),
		writeData,
		process,
		address,
		size,
		UserMode,
		&bytesWritten
	);

	ObDereferenceObject(process);

	return status;
}

NTSTATUS HandleWriteRequest(ULONG processId, PVOID address, PVOID writeData, ULONG size) {
	PEPROCESS process;

	NTSTATUS status = PsLookupProcessByProcessId((HANDLE)processId, &process);

	if (!NT_SUCCESS(status)) {
		return status;
	}

	SIZE_T bytesWritten = 0;
	status = MmCopyVirtualMemory(
		PsGetCurrentProcess(),
		writeData,
		process,
		address,
		size,
		UserMode,
		&bytesWritten
	);

	ObDereferenceObject(process);

	return status;
}