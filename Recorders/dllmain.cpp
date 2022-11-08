#include "pch.h"
#include "game_reversals/framework/helpers.h"
#include "game_reversals/framework/il2cpp-init.cpp"
#include "data_recorders/RecorderMain.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

DWORD WINAPI RunRecorderThread(LPVOID lpParam)
{
    //LOG_DEBUG("Spawned recorder thread.");
    RecorderMain rm;
    rm.Init();
    rm.Run();

    return 0;
}

void Run(HMODULE* phModule)
{
    //init console
    il2cppi_new_console();

    while (GetModuleHandle("UserAssembly.dll") == nullptr)
    {
        Sleep(2000);
    }

    //bypass mhyrot2
    init_static_offsets();

    //init recorders
    CreateThread(nullptr, 0, RunRecorderThread, phModule, 0, nullptr);
}