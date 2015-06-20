#include "r3e.h"
#include "utils.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <tchar.h>

#define ALIVE_SEC 600
#define INTERVAL_MS 100

HANDLE map_handle = INVALID_HANDLE_VALUE;
r3e_shared* map_buffer = NULL;

HANDLE map_open()
{
    return OpenFileMapping(
        FILE_MAP_READ,
        FALSE,
        TEXT(R3E_SHARED_MEMORY_NAME));
}

BOOL map_exists()
{
    HANDLE handle = map_open();

    if (handle != NULL)
        CloseHandle(handle);
        
    return handle != NULL;
}

int map_init()
{
    map_handle = map_open();

    if (map_handle == NULL)
    {
        wprintf_s(L"Failed to open mapping");
        return 1;
    }

    map_buffer = (r3e_shared*)MapViewOfFile(map_handle, FILE_MAP_READ, 0, 0, sizeof(r3e_shared));
    if (map_buffer == NULL)
    {
        wprintf_s(L"Failed to map buffer");
        return 1;
    }

    return 0;
}

void map_close()
{
    if (map_buffer) UnmapViewOfFile(map_buffer);
    if (map_handle) CloseHandle(map_handle);
}

int main()
{
    clock_t clk_start = 0, clk_last = 0;
    clock_t clk_delta_ms = 0, clk_elapsed = 0;
    int err_code = 0;
    BOOL mapped_r3e = FALSE;

    clk_start = clock();
    clk_last = clk_start;

    wprintf_s(L"Looking for RRRE.exe...\n");

    for(;;)
    {
        clk_elapsed = (clock() - clk_start) / CLOCKS_PER_SEC;
        if (clk_elapsed >= ALIVE_SEC)
            break;

        clk_delta_ms = (clock() - clk_last) / CLOCKS_PER_MS;
        if (clk_delta_ms < INTERVAL_MS)
        {
            Sleep(1);
            continue;
        }

        clk_last = clock();

        if (!mapped_r3e && is_r3e_running() && map_exists())
        {
            wprintf_s(L"Found RRRE.exe, mapping shared memory...\n");

            err_code = map_init();
            if (err_code)
                return err_code;

            wprintf_s(L"Memory mapped successfully\n");

            mapped_r3e = TRUE;
            clk_start = clock();
        }

        if (mapped_r3e)
        {
            if (map_buffer->gear > -2)
            {
                wprintf_s(L"Gear: %i\n", map_buffer->gear);
            }

            if (map_buffer->engineRps > -1.f)
            {
                wprintf_s(L"RPM: %.3f\n", map_buffer->engineRps * RPS_TO_RPM);
                wprintf_s(L"Speed: %.3f km/h\n", map_buffer->carSpeed * MPS_TO_KPH);
            }

            wprintf_s(L"\n");
        }
    }

    map_close();

    wprintf_s(L"All done!");
    system("PAUSE");

    return 0;
}