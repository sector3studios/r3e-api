#include "utils.h"

#include <TlHelp32.h>
#include <tchar.h>

BOOL is_process_running(const TCHAR* name)
{
    HANDLE snapshot = NULL;
    PROCESSENTRY32 entry;

    ZeroMemory(&entry, sizeof(entry));
    entry.dwSize = sizeof(PROCESSENTRY32);

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(snapshot, &entry))
    {
        while (Process32Next(snapshot, &entry))
        {
            if (_tcscmp(entry.szExeFile, name) == 0)
                return TRUE;
        }
    }

    return FALSE;
}

BOOL is_r3e_running()
{
    return is_process_running(TEXT("RRRE.exe"));
}