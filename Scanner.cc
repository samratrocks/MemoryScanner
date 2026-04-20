#include <windows.h>
#include <iostream>
#include "Scanner.h"

using namespace std;


LPCWSTR Scanner::version() {
	return L"MemScanner v0.01";
}

HANDLE Scanner::loadProcess(const WCHAR* pathToExe) {

	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);

	CreateProcessW(
		pathToExe,   // lpApplicationName
		NULL,        // lpCommandLine
		NULL,        // lpProcessAttributes
		NULL,        // lpThreadAttributes
		FALSE,       // bInheritHandles
		0,           // dwCreationFlags
		NULL,        // lpEnvironment
		NULL,        // lpCurrentDirectory
		&si,         // lpStartupInfo
		&pi          // lpProcessInformation
	);

	this->processHandle = pi.hProcess;
	return this->processHandle;
}

void Scanner::closeProcess() {
	CloseHandle(this->processHandle);
}

void Scanner::attachToProcess(DWORD pid) {
	// use the process id to attach to a process
	if (!DebugActiveProcess(pid)) {
		cout << "Unable to attach to process." << endl;
		return;
	}
}

void Scanner::loadNotepad() {
	if (!Scanner::loadProcess(L"C:\\Windows\\System32\\notepad.exe")) {
		cerr << "Unable to load notepad." << endl;
		exit;
	}

	// Load notepad
	return;
}