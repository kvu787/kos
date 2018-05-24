#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>

void hang(void)
{
	while (true)
	{
	}
}

void error(LPCSTR message)
{
	printf("Error: %s\r\n", message);
	exit(EXIT_FAILURE);
}

char *strerror_m(errno_t errnum)
{
	size_t bufferSize = 512 * sizeof(char);
	char *buffer = (char *)malloc(bufferSize);
	strerror_s(buffer, bufferSize, errnum);
	return buffer;
}

uint8_t *ReadFileContents(const char *path, long *pFileSize)
{
	// Open file
	FILE *file;
	errno_t err = fopen_s(&file, path, "rb");
	if (err != 0)
	{
		printf("ReadFileContents: Error while opening %s\r\n", path);
		error(strerror_m(err));
	}

	// Get file size
	fseek(file, 0L, SEEK_END);
	long fileSize = ftell(file);
	*pFileSize = fileSize;
	rewind(file);

	// Allocate buffer
	uint8_t *fileContents = (uint8_t *)malloc(fileSize * sizeof(uint8_t));
	uint8_t *fileContentsCurrent = fileContents;

	// Read file into buffer
	while (fileSize > 0)
	{
		*fileContentsCurrent++ = (uint8_t)fgetc(file);
		fileSize--;
	}

	return fileContents;
}

char ReadCharUart(HANDLE handle)
{
	DWORD numBytesRead;
	char c;
	if (!ReadFile(handle, &c, sizeof(c), &numBytesRead, NULL))
	{
		error("ReadFile");
	}
	if (numBytesRead != 1)
	{
		error("ReadFile: numBytesRead != 1");
	}
	return c;
}

void WriteByteUart(HANDLE handle, uint8_t byte)
{
	DWORD numBytesWritten;
	BOOL ok = WriteFile(handle, &byte, sizeof(byte), &numBytesWritten, NULL);
	if (!ok)
	{
		error("WriteFile: !ok");
	}
	if (numBytesWritten != 1)
	{
		error("WriteFile: numBytesWritten != 1");
	}
}


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Not enough arguments\r\n");
		printf("Usage: sender.exe <com port> <kernel file path>\r\n");
		exit(EXIT_FAILURE);
	}

	// Read command line arguments
	char *ComPort = argv[1];
	char *KernelFilePath = argv[2];

	// Build COM port path
	size_t ComPortPathSize = (strlen("\\\\.\\") + strlen(ComPort) + 1) * sizeof(char);
	char *ComPortPath = (char *)malloc(ComPortPathSize);
	_snprintf_s(ComPortPath, ComPortPathSize, ComPortPathSize - 1, "\\\\.\\%s", ComPort);

	// Open serial port
	BOOL ok;
	HANDLE handle;
	handle = CreateFile(ComPortPath,   // port name
		GENERIC_READ | GENERIC_WRITE,  // Read/Write
		0,                             // No Sharing
		0,                             // No Security
		OPEN_EXISTING,                 // Open existing port only
		0,                             // Non Overlapped I/O
		NULL);                         // Null for Comm Devices
	if (handle == INVALID_HANDLE_VALUE)
	{
		error("CreateFile");
	}

	// Configure serial port
	DCB dcb;
	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	ok = BuildCommDCB("115200,n,8,1", &dcb);
	if (!ok)
	{
		error("BuildCommDCB");
	}
	ok = SetCommState(handle, &dcb);
	if (!ok)
	{
		error("SetCommState");
	}

	// Set timeouts to zero, so all operations are blocking
	COMMTIMEOUTS commTimeouts =
	{
		.ReadIntervalTimeout = 0,
		.ReadTotalTimeoutMultiplier = 0,
		.ReadTotalTimeoutConstant = 0,
		.WriteTotalTimeoutMultiplier = 0,
		.WriteTotalTimeoutConstant = 0,
	};
	ok = SetCommTimeouts(handle, &commTimeouts);
	if (!ok)
	{
		error("SetCommTimeouts");
	}

	// Read kernel file
	long fileSize;
	uint8_t *kernel = ReadFileContents(KernelFilePath, &fileSize);

	// Transmit kernel size in little endian
	uint32_t fileSizeUint32 = (uint32_t)fileSize;
	for (int i = 0; i < 4; ++i)
	{
		uint8_t byte = (uint8_t)(fileSizeUint32 & 0xff);
		WriteByteUart(handle, byte);
		fileSizeUint32 >>= 8;
	}

	// Transmit kernel
	unsigned long bcount = 0;
	while (fileSize > 0)
	{
		WriteByteUart(handle, *kernel++);
		--fileSize;
	}

	// Close serial port
	CloseHandle(handle);

	return 0;
}
