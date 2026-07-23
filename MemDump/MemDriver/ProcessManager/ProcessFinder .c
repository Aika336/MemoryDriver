#include "ProcessFinder.h"

PEPROCESS FindProcessByName(UCHAR targetName) {
    PEPROCESS process = NULL;
    BOOLEAN found = FALSE;

    const int pidDevider = 4;
    const int maxProcessName = 15;
    int maxProcessIdes = Exponent(2, 16);

    for (int i = pidDevider; i <= maxProcessIdes; i += pidDevider) {
        PEPROCESS candidate = NULL;

        NTSTATUS status = PsLookupProcessByProcessId((HANDLE)i, &candidate);
        if (!NT_SUCCESS(status)) {
            continue;
        }

        PCHAR processName = PsGetProcessImageFileName(candidate);

        if (processName && strncmp(processName, targetName, maxProcessName) == 0) {
            process = candidate;
            found = TRUE;
            break;
        }

        ObDereferenceObject(candidate);
    }

    return process;
}