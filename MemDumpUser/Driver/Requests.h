#include <Windows.h>

typedef struct READ_REQUEST {
	PCHAR targetName;
	ULONG handle;
	ULONG_PTR  Address;
	ULONG Size;
} READ_REQUEST, * PREAD_REQUEST;

typedef struct WRITE_REQUEST {
	PCHAR targetName;
	ULONG handle;
	ULONG_PTR targetAddress;
	ULONG_PTR dataBuffer;
	ULONG Size;
} WRITE_REQUEST, * PWRITE_REQUEST;