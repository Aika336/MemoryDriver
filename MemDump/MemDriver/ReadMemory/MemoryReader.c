#include "../ReadMemory/MemoryReader.h"
#include "../ProcessManager/ProcessFinder.h"

NTSTATUS NameReadRequest(PCHAR targetName, PVOID address, ULONG size, PVOID outBuffer) {
    PEPROCESS process = FindProcessByName(targetName);
    
    if (!process) {
        return STATUS_NOT_FOUND;
    }

    SIZE_T bytesRead = 0;
    NTSTATUS status = MmCopyVirtualMemory(
        process,
        address,
        PsGetCurrentProcess(),
        outBuffer,
        size,
        KernelMode,
        &bytesRead
    );

    ObDereferenceObject(process);
    return status;
}

NTSTATUS HandleReadRequest(ULONG pid, PVOID address, ULONG size, PVOID outBuffer) {
    PEPROCESS targetProcess;

    NTSTATUS status = PsLookupProcessByProcessId((HANDLE)pid, &targetProcess);

    if (!NT_SUCCESS(status)) {
        return status;
    }

    SIZE_T bytesRead = 0;
    status = MmCopyVirtualMemory(
        targetProcess,
        address,
        PsGetCurrentProcess(),
        outBuffer,
        size,
        KernelMode,
        &bytesRead
    );
    
    ObDereferenceObject(targetProcess);

    return status;
}