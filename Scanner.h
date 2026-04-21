#pragma once
#include <windows.h>
#include <vector>


class Scanner {
private:
	HANDLE processHandle;
public:
	static LPCWSTR version();
	HANDLE loadProcess(const WCHAR* pathToExe);
	void closeProcess();
	void loadNotepad();
	void attachToProcess(DWORD pid);
	void enumerateRegions();
	bool readRegion(LPCVOID baseAddress, SIZE_T size, std::vector<BYTE>& out);
};
