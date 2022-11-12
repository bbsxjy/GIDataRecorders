#pragma once
using namespace app;
//For YuanShen v3.2
#define DO_APP_FUNC(a, r, n, p)  r (*n) p
#define DO_APP_FUNC_METHODINFO(a, n) struct MethodInfo ** n

//ImageBase = UserAssembly.dll
DO_APP_FUNC(0x08EBB6D0, String*, Marshal_PtrToStringAnsi, (void* ptr, MethodInfo* method));
DO_APP_FUNC(0x097086E0, Byte__Array*, Application_RecordUserData, (int32_t nType, MethodInfo* method));
DO_APP_FUNC(0x0971D9D0, GameObject*, GameObject_Find, (String* name, MethodInfo* method));
DO_APP_FUNC(0x0971DF30, Transform*, GameObject_get_transform, (GameObject* __this, MethodInfo* method));
DO_APP_FUNC(0x09654F10, Vector3, Transform_get_eulerAngles, (Transform* __this, MethodInfo* method));
DO_APP_FUNC(0x09655440, void, Transform_set_eulerAngles, (Transform* __this, Vector3 value, MethodInfo* method));
DO_APP_FUNC(0x096E4A70, float, Input_GetAxis, (String* axisName, MethodInfo* method));
DO_APP_FUNC(0x02F5A7D0, Vector3, ActorUtils_GetAvatarPos, (MethodInfo* method));
DO_APP_FUNC(0x02F63760, void, ActorUtils_SetAvatarPos, (Vector3 pos, MethodInfo* method));
DO_APP_FUNC(0x09708DC0, int32_t, Application_get_targetFrameRate, (MethodInfo* method));
DO_APP_FUNC(0x09709200, void, Application_set_targetFrameRate, (int32_t value, MethodInfo* method));
DO_APP_FUNC(0x09672C10, bool, Cursor_get_visible, (MethodInfo* method));
DO_APP_FUNC(0x09672C30, void, Cursor_set_visible, (bool value, MethodInfo* method));
DO_APP_FUNC(0x096388A0, int32_t, Screen_get_width, (MethodInfo* method));
DO_APP_FUNC(0x09638830, int32_t, Screen_get_height, (MethodInfo* method));
DO_APP_FUNC(0x020ADA60, void*, Singleton_GetInstance, (MethodInfo* method));
//Signature = 40 53 48 83 EC ?? 45 33 C0 48 8B DA
DO_APP_FUNC(0x027CA230, Il2CppArray*, il2cpp_array_new, (Il2CppClass* elementTypeInfo, il2cpp_array_size_t length));
DO_APP_FUNC_METHODINFO(0x0CEACDC0, Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo);

