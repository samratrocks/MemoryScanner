#pragma once
#include <windows.h>
#include <vector>


class Scanner {
private:
	HANDLE processHandle;
	DWORD currentPid;
	BOOL debug;
	std::vector<uintptr_t> hits;	// record every place we find the value

	enum HandleSource {
		NONE,
		LAUNCHED,
		ATTACHED
	} handleSource;

public:
	static LPCWSTR version();
	HANDLE loadProcess(const WCHAR* pathToExe);
	void closeProcess();
	void loadNotepad();
	void attachAsDebugger(DWORD pid);
	void enumerateRegions();
	bool readRegion(LPCVOID baseAddress, SIZE_T size, std::vector<BYTE>& out);
	HANDLE openProcessByPid(DWORD pid);
	void scanForValue(DWORD value);
};
