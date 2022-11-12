#include "game-functions.h"

GameFunctions& GameFunctions::GetInstance()
{
    static GameFunctions ctx = GameFunctions();
    return ctx;
}

void GameFunctions::InitStaticOffsets()
{
    printf("Initing static offsets.\n");
    auto baseUAAddress = (uintptr_t)GetModuleHandleW(L"UserAssembly.dll");
    printf("UserAssembly.dll Starts at %p.\n", (void*)baseUAAddress);
    auto baseUPAddress = (uintptr_t)GetModuleHandleW(L"UnityPlayer.dll");
    printf("UnityPlayer.dll Starts at %p.\n", (void*)baseUPAddress);

    Marshal_PtrToStringAnsi = (Marshal_PtrToStringAnsiType)(baseUAAddress + MARSHAL_PTRTOSTRINGANSI);
    Application_RecordUserData = (Application_RecordUserDataType)(baseUAAddress + APPLICATION_RECORDUSERDATA);
    GameObject_Find = (GameObject_FindType)(baseUAAddress + GAMEOBJECT_FIND);
    GameObject_get_transform = (GameObject_get_transformType)(baseUAAddress + GAMEOBJECT_GET_TRANSFORM);
    Transform_get_eulerAngles = (Transform_get_eulerAnglesType)(baseUAAddress + TRANSFORM_GET_EULERANGLES);
    Transform_set_eulerAngles = (Transform_set_eulerAnglesType)(baseUAAddress + TRANSFORM_SET_EULERANGLES);
    Input_GetAxis = (Input_GetAxisType)(baseUAAddress + INPUT_GETAXIS);
    ActorUtils_GetAvatarPos = (ActorUtils_GetAvatarPosType)(baseUAAddress + ACTORUTILS_GETAVATARPOS);
    ActorUtils_SetAvatarPos = (ActorUtils_SetAvatarPosType)(baseUAAddress + ACTORUTILS_SETAVATARPOS);
    Application_get_targetFrameRate = (Application_get_targetFrameRateType)(baseUAAddress + APPLICATION_GET_TARGETFRAMERATE);
    Application_set_targetFrameRate = (Application_set_targetFrameRateType)(baseUAAddress + APPLICATION_SET_TARGETFRAMERATE);
    Cursor_get_visible = (Cursor_get_visibleType)(baseUAAddress + CURSOR_GET_VISIBLE);
    Cursor_set_visible = (Cursor_set_visibleType)(baseUAAddress + CURSOR_SET_VISIBLE);
    Screen_get_width = (Screen_get_widthType)(baseUAAddress + SCREEN_GET_WIDTH);
    Screen_get_height = (Screen_get_heightType)(baseUAAddress + SCREEN_GET_HEIGHT);
    Singleton_GetInstance = (Singleton_GetInstanceType)(baseUAAddress + SINGLETON_GETINSTANCE);
    il2cpp_array_new = (il2cpp_array_newType)(baseUAAddress + IL2CPP_ARRAY_NEW);
    Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo = (Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfoType)(baseUAAddress + SINGLETON_1_MOLEMOLE_ENTITYMANAGER__GET_INSTANCE__METHODINFO);
    Unity_RecordUserData = (Unity_RecordUserDataType)(baseUPAddress + UNITY_RECORD_USER_DATA);
    GetIl2Classes = (GetIl2ClassesType)(baseUPAddress + GETIL2CLASSES);
}

app::String* GameFunctions::string_to_il2cppi(std::string input)
{
    return Marshal_PtrToStringAnsi((void*)input.c_str(), nullptr);
}
