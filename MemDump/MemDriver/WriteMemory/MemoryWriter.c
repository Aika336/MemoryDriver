#include "MemoryWriter.h"
#include "../ProcessManager/ProcessFinder.h"

NTSTATUS NameWriteRequest(PCHAR targetName, PVOID address, PVOID writeData, ULONG size) {
	PEPROCESS process = FindProcessByName(targetName);

	if (!process) {
		return STATUS_NOT_FOUND;
	}

	KAPC_STATE apcState;
	KeStackAttachProcess(process, &apcState);

	NTSTATUS status = STATUS_UNSUCCESSFUL;

	__try {
		ProbeForWrite(address, size, 1);
		RtlCopyMemory(address, writeData, size);
		status = STATUS_SUCCESS;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		status = GetExceptionCode();
	}
	KeUnstackDetachProcess(&apcState);
	ObDereferenceObject(process);

	return status;
}