#include "game-functions.h"
#include "GIProtectionBypass.h"
#include "ProcessHelper.h"
//Orignal Function Pointers
Unity_RecordUserDataType OriginalUnity_RecordUserDataFunc = nullptr;

app::Byte__Array* __fastcall OnRecordUserData(int32_t nType)
{
    if (GIProtectionBypass::GetInstance().m_CorrectSignatures.count(nType))
    {
        Il2CppClass* byteClass = GameFunctions::GetInstance().GetIl2Classes()[0x25];
        auto& content = GIProtectionBypass::GetInstance().m_CorrectSignatures[nType];
        auto newArray = (app::Byte__Array*)GameFunctions::GetInstance().il2cpp_array_new(byteClass, content.size());
        memmove_s(newArray->vector, content.size(), content.data(), content.size());
        return newArray;
    }
    app::Byte__Array* result = OriginalUnity_RecordUserDataFunc(nType);

    auto resultArray = TO_UNI_ARRAY(result, byte);

    auto length = resultArray->length();
    if (length == 0) {
        return result;
    }

    auto stringValue = std::string((char*)result->vector, length);
    GIProtectionBypass::GetInstance().m_CorrectSignatures[nType] = stringValue;

    //printf("Sniffed correct signature for type %d value '%s'\n", nType, stringValue.c_str());

    return result;
}

GIProtectionBypass& GIProtectionBypass::GetInstance()
{
    static GIProtectionBypass ctx = GIProtectionBypass();
    return ctx;
}

void GIProtectionBypass::InstallHooks()
{
    //printf("Installing hooks.\n");
    auto baseUAAddress = (uintptr_t)GetModuleHandleW(L"UserAssembly.dll");
    auto baseUPAddress = (uintptr_t)GetModuleHandleW(L"UnityPlayer.dll");
    if (MH_Initialize() != MH_OK)
    {
        printf("[´íÎó] MH ³õÊ¼»¯Ê§°Ü£¡\n");
    }

    if (MH_CreateHook((GameFunctions::GetInstance().Unity_RecordUserData), &OnRecordUserData, reinterpret_cast<LPVOID*>(&OriginalUnity_RecordUserDataFunc)))
    {
        printf("[´íÎó] UnityRecordUserData ³õÊ¼»¯Ê§°Ü£¡\n");
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        printf("[´íÎó] MH Æô¶¯Ê§°Ü£¡\n");
    }
    //else {
    //    printf("Hooks enabled.\n");
    //}
}

void GIProtectionBypass::InitBypass()
{
    //printf("Initing game protection bypass.\n");
    // Record signatures.
    for (int i = 0; i < 4; i++) {
        //printf("Emulating call of RecordUserData with type %d\n", i);
        GameFunctions::GetInstance().Application_RecordUserData(i, nullptr);
    }

    // Close Mhyprot2 handle.
    //printf("Trying to close mhyprot handle.\n");
    if (!ProcessHelper::CloseHandleByName(L"\\Device\\mhyprot2"))
        //printf("The Mhyprot2 handle was successfully closed.\n");
        printf("[´íÎó] MHP ³õÊ¼»¯Ê§°Ü£¡\n");
}
