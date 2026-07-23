#include "MemoryWriter.h"
#include "../ProcessManager/ProcessFinder.h"

NTSTATUS NameWriteRequest(PCHAR targetName, PVOID address, PVOID writeData, ULONG size) {
	PEPROCESS process = FindProcessByName(targetName);

	if (!process) {
		return STATUS_NOT_FOUND;
	}

	NTSTATUS status = STATUS_UNSUCCESSFUL;
	PVOID buffer = ExAllocatePool2(POOL_FLAG_PAGED, (SIZE_T)size, 'WrNm');

	if (!buffer) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	__try {
		RtlCopyMemory(buffer, writeData, size);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return GetExceptionCode();
	}

	KAPC_STATE apcState;
	KeStackAttachProcess(process, &apcState);

	__try {
		RtlCopyMemory(address, buffer, size);
		status = STATUS_SUCCESS;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		status = GetExceptionCode();
	}
	KeUnstackDetachProcess(&apcState);
	ObDereferenceObject(process);

	ExFreePool(buffer);

	return status;
}

NTSTATUS HandleWriteRequest(ULONG processId, PVOID address, PVOID writeData, ULONG size) {
	PEPROCESS process;

	NTSTATUS status = PsLookupProcessByProcessId((HANDLE)processId, &process);

	if (!NT_SUCCESS(status)) {
		return status;
	}

	PVOID buffer = ExAllocatePool2(POOL_FLAG_PAGED, (SIZE_T)size, 'WrId');

	if (!buffer) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	__try {
		RtlCopyMemory(buffer, writeData, size);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return GetExceptionCode();
	}

	KAPC_STATE apcState;
	KeStackAttachProcess(process, &apcState);

	__try {
		RtlCopyMemory(address, buffer, size);
		status = STATUS_SUCCESS;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		status = GetExceptionCode();
	}

	KeUnstackDetachProcess(&apcState);
	ObDereferenceObject(process);

	ExFreePool(buffer);

	return status;
}