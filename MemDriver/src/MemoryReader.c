#include "MemoryReader.h"
#include "../../Math/math.h"

NTSTATUS NameReadRequest(UCHAR* targetName, PVOID address, ULONG size, PVOID outBuffer) {
    PEPROCESS process = NULL;
    BOOLEAN found = FALSE;

    const int pidDevider = 4;
    const int maxProcessName = 15;
    const int maxPid = Exponent(2,16);
    
    for (int i = pidDevider; i <= maxPid; i += pidDevider) {
        PEPROCESS candidate = NULL;

        NTSTATUS status = PsLookupProcessByProcessId((HANDLE)i, &candidate);
        if (!NT_SUCCESS(status)) {
            continue;
        }

        PCHAR processName = PsGetProcessImageFileName(candidate);

        if (processName && strncmp(processName, (char*)targetName, maxProcessName) == 0) {
            process = candidate;
            found = TRUE;
            break;
        }

        ObDereferenceObject(candidate);
    }
    
    if (!found) {
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
