#include "../ReadMemory/MemoryReader.h"
#include "../ProcessManager/ProcessFinder.h"

NTSTATUS NameReadRequest(PCHAR targetName, PVOID address, ULONG size, PVOID outBuffer) {
    PEPROCESS process = FindProcessByName(targetName);
    
    if (!process) {
        return STATUS_NOT_FOUND;
    }

    KAPC_STATE apcState;
    KeStackAttachProcess(process, &apcState);

    NTSTATUS status = STATUS_UNSUCCESSFUL;

    __try {
        ProbeForRead(address, size, 1);
        RtlCopyMemory(outBuffer, address, size);
        status = STATUS_SUCCESS;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        status = GetExceptionCode();
    }

    KeUnstackDetachProcess(&apcState);
    ObDereferenceObject(process);
    return status;
}

NTSTATUS HandleReadRequest(ULONG pid, PVOID address, ULONG size, PVOID outBuffer) {
    PEPROCESS targetProcess;

    NTSTATUS status = PsLookupProcessByProcessId((HANDLE)pid, &targetProcess);

    if (!NT_SUCCESS(status)) {
        return status;
    }

    KAPC_STATE apcState;
    KeStackAttachProcess(targetProcess, &apcState);

    __try {
        ProbeForRead(address, size, 1);
        RtlCopyMemory(outBuffer, address, size);
        status = STATUS_SUCCESS;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        status = GetExceptionCode();
    }

    KeUnstackDetachProcess(&apcState);
    ObDereferenceObject(targetProcess);

    return status;
}