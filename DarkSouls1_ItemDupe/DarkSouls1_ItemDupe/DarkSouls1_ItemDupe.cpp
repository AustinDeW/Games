#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>

using namespace std;

DWORD_PTR GetProcBaseAddress(const wchar_t* procName);
DWORD GetPID(const wchar_t* procName);

int main()
{
	//cout << hex << GetProcBaseAddress(L"notepad.exe") << dec << endl;
	cout << hex << GetProcBaseAddress(L"notepad.exe") << dec << endl;
	//cout << GetPID(L"notepad.exe");

	char ch = '\0'; cin >> ch;
	return 0;
}

DWORD_PTR GetProcBaseAddress(const wchar_t* procName)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetPID(procName));
	MODULEENTRY32 moduEntry;
	DWORD_PTR procBaseA = 0xFFFFFFFF;

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		cout << "Could not get snapshot of " << procName << endl;
		return NULL;
	}

	moduEntry.dwSize = sizeof(MODULEENTRY32);
	
	if (!Module32First(snapshot, &moduEntry))
	{
		cout << "Could not find first module of " << procName << endl;
		CloseHandle(snapshot);
		return NULL;
	}

	// Find module of .exe
	do
	{
		if (!_wcsicmp(moduEntry.szModule, procName))
		{
			procBaseA = (DWORD_PTR)moduEntry.modBaseAddr;
			break;
		}
	} while (Module32Next(snapshot, &moduEntry));

	if (procBaseA == 0xFFFFFFFF)
	{
		system("cls");
		cout << "Failed to find module " << procName << endl;
	}

	CloseHandle(snapshot);

	return procBaseA;
}

DWORD GetPID(const wchar_t* procName)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &pe32))
	{
		while (Process32Next(snapshot, &pe32))
		{
			if (!_wcsicmp(pe32.szExeFile, procName))
			{
				return pe32.th32ProcessID;
			}
		}
	}

	return NULL;
}