#include <windows.h>
#include <iostream>
#include "Scanner.h"
#include <vector>

using namespace std;





void Scanner::enumerateRegions() {
	if (this->processHandle == NULL) {
		return;
	 }

	MEMORY_BASIC_INFORMATION mbi;
	uintptr_t addr = 0;

	while (VirtualQueryEx(this->processHandle, (LPCVOID)addr, &mbi, sizeof(mbi)) == sizeof(mbi)) {
		if (mbi.State == MEM_COMMIT
			&& !(mbi.Protect & PAGE_GUARD)
			&& !(mbi.Protect & PAGE_NOACCESS)
			&& (mbi.Protect & PAGE_READWRITE)) {

			// Process the memory region
			cout << "Base: " << mbi.BaseAddress
				<< "\t\tSize: " << mbi.RegionSize
				<< "\tCurrent address: " << addr
				<< "\tNext address: " << (uintptr_t)mbi.BaseAddress + mbi.RegionSize
				<< endl;
		}

		addr = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
	}
}



HANDLE Scanner::openProcessByPid(DWORD pid) {
	this->closeProcess();						// let's close the current process before we open another
	HANDLE processHandle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);

	if (!processHandle) {
		cout << "Unable to open process by id: " << GetLastError() << endl;
		return NULL;
	}

	this->processHandle = processHandle;
	this->handleSource = ATTACHED;
	this->currentPid = pid;

	return processHandle;
}

LPCWSTR Scanner::version() {
	return L"MemScanner v0.01";
}

HANDLE Scanner::loadProcess(const WCHAR* pathToExe) {

	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);

	BOOL isProcessCreated = CreateProcessW(
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

	if (!isProcessCreated) {
		// throw some error
		cout << GetLastError() << endl;
		return NULL;
	}

	CloseHandle(pi.hThread);
	this->processHandle = pi.hProcess;
	this->handleSource = LAUNCHED;
	this->currentPid = pi.dwProcessId;
	cout << "this->processHandle: " << this->processHandle << endl;
	return this->processHandle;
}

void Scanner::closeProcess() {
	if (!this->processHandle) {
		cout << "No process handle" << endl;
		return;
	}

	if (!CloseHandle(this->processHandle)) {
		cout << "CloseHandle failed: " << GetLastError() << endl;
	}

	this->processHandle = NULL;
	handleSource = NONE;
	this->currentPid = 0;
}

void Scanner::attachAsDebugger(DWORD pid) {
	// use the process id to attach to a process
	if (!DebugActiveProcess(pid)) {
		cout << "Unable to attach to process." << endl;
		return;
	}
}

void Scanner::loadNotepad() {
	if (!Scanner::loadProcess(L"C:\\Windows\\System32\\notepad.exe")) {
		cerr << "Unable to load notepad: " << GetLastError() << endl;
	}
}

bool Scanner::readRegion(LPCVOID baseAddress, SIZE_T size, std::vector<BYTE>& out) {
	cout << "Stub function not implemened: [readRegion]" << endl;
	return false;
}