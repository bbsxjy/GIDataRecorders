#include <cstdint>
#include <Windows.h>
#include <stdio.h>
#include "GIProtectionBypass.h"
#include "RecorderMain.h"


void InitNewConsole() {
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
}

DWORD WINAPI RunRecorderThread(LPVOID lpParam)
{
    RecorderMain rm;
    rm.Init();
    rm.Run();

    return 0;
}

void Run(HMODULE phModule)
{
    ProcessHelper::SetCurrentPath(ProcessHelper::GetModulePaths(phModule));

    InitNewConsole();

    while (GetModuleHandle("UserAssembly.dll") == nullptr)
    {
        printf("UserAssembly.dll isn't initialized, waiting for 2 sec.\n");
        Sleep(2000);
    }

    printf("Waiting 10sec for game initialize.\n");
    Sleep(10000);

    GameFunctions::GetInstance().InitStaticOffsets();
    GIProtectionBypass::GetInstance().InstallHooks();
    GIProtectionBypass::GetInstance().InitBypass();

    CreateThread(nullptr, 0, RunRecorderThread, phModule, 0, nullptr);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Run, hModule, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}