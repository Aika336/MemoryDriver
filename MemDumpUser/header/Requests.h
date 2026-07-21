#include <Windows.h>

typedef struct _READ_REQUEST {
	UCHAR* targetName;
	ULONG handle;
	ULONG_PTR  Address;
	ULONG Size;
} READ_REQUEST, * PREAD_REQUEST;