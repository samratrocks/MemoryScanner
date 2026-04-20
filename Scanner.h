#pragma once
#include <windows.h>


class Scanner {
private:
	HANDLE processHandle;
public:
	static LPCWSTR version();
	HANDLE loadProcess(const WCHAR* pathToExe);
	void closeProcess();
	void loadNotepad();
	void attachToProcess(DWORD pid);
};
