#include <windows.h>
#include <iostream>
#include "Scanner.h"
#include <vector>

using namespace std;

/*
 * TODO:
 *
 * - Add: enum HandleSource { NONE, LAUNCHED, ATTACHED } handleSource; DWORD currentPid;
 * - Rename attachToProcess -> attachAsDebugger (keep for debugger half)
 * - Add openProcessByPid(DWORD pid): close existing handle first, OpenProcess w/
 *   PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, log GetLastError on fail
 * - loadProcess: set handleSource = LAUNCHED, store pi.dwProcessId
 * - closeProcess: reset handleSource/currentPid/processHandle; doesn't kill process
 * - (Optional) terminateAndClose() guarded on LAUNCHED
 * - GUI: PID field, Attach/Close buttons, show currentPid + handleSource, surface errors
 */


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
	cout << "this->processHandle: " << this->processHandle << endl;
	return this->processHandle;
}

void Scanner::closeProcess() {
	if (!this->processHandle) {
		cout << "No process handle" << endl;
		return;
	}

	try {
		CloseHandle(this->processHandle);
	}
	catch (int errorCode) {
		cout << "Couldn't close process, exiting anyways." << endl;
		cout << "Error Code "  << errorCode << endl;
	}

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

void Scanner::enumerateRegions() {
	if (!this->processHandle) {
		cout << "Process handle is missing [this->processHandle]" << endl;
	}
}

bool Scanner::readRegion(LPCVOID baseAddress, SIZE_T size, std::vector<BYTE>& out) {
	cout << "Stub function not implemened: [readRegion]" << endl;
	return false;
}