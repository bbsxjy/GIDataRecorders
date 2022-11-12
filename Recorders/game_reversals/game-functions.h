#pragma once
#include "pch.h"

using namespace app;
//ImageBase = UserAssembly.dll
#define MARSHAL_PTRTOSTRINGANSI 0x08EBB6D0
#define APPLICATION_RECORDUSERDATA 0x097086E0
#define GAMEOBJECT_FIND  0x0971D9D0
#define GAMEOBJECT_GET_TRANSFORM  0x0971DF30
#define TRANSFORM_GET_EULERANGLES  0x09654F10
#define TRANSFORM_SET_EULERANGLES  0x09655440
#define INPUT_GETAXIS  0x096E4A70
#define ACTORUTILS_GETAVATARPOS  0x02F5A7D0
#define ACTORUTILS_SETAVATARPOS  0x02F63760
#define APPLICATION_GET_TARGETFRAMERATE  0x09708DC0
#define APPLICATION_SET_TARGETFRAMERATE  0x09709200
#define CURSOR_GET_VISIBLE  0x09672C10
#define CURSOR_SET_VISIBLE 0x09672C30
#define SCREEN_GET_WIDTH  0x096388A0
#define SCREEN_GET_HEIGHT 0x09638830
//Signature = 40 53 48 83 EC ?? 45 33 C0 48 8B DA
#define IL2CPP_ARRAY_NEW 0x027CA230
#define SINGLETON_GETINSTANCE  0x020ADA60
#define SINGLETON_1_MOLEMOLE_ENTITYMANAGER__GET_INSTANCE__METHODINFO  0x0CEACDC0
//ImageBase = UnityPlayer.dll
#define UNITY_RECORD_USER_DATA 0x00BA4D80
#define GETIL2CLASSES 0x00B41920

typedef String* (__stdcall* Marshal_PtrToStringAnsiType) (void* ptr, MethodInfo* method);
typedef Byte__Array* (__stdcall* Application_RecordUserDataType) (int32_t nType, MethodInfo* method);
typedef GameObject* (__stdcall* GameObject_FindType) (String* name, MethodInfo* method);
typedef Transform* (__stdcall* GameObject_get_transformType) (GameObject* __this, MethodInfo* method);
typedef Vector3(__stdcall* Transform_get_eulerAnglesType) (Transform* __this, MethodInfo* method);
typedef void(__stdcall* Transform_set_eulerAnglesType) (Transform* __this, Vector3 value, MethodInfo* method);
typedef float(__stdcall* Input_GetAxisType) (String* axisName, MethodInfo* method);
typedef Vector3(__stdcall* ActorUtils_GetAvatarPosType) (MethodInfo* method);
typedef void(__stdcall* ActorUtils_SetAvatarPosType) (Vector3 pos, MethodInfo* method);
typedef int32_t(__stdcall* Application_get_targetFrameRateType) (MethodInfo* method);
typedef void(__stdcall* Application_set_targetFrameRateType) (int32_t value, MethodInfo* method);
typedef bool(__stdcall* Cursor_get_visibleType) (MethodInfo* method);
typedef void(__stdcall* Cursor_set_visibleType) (bool value, MethodInfo* method);
typedef int32_t(__stdcall* Screen_get_widthType) (MethodInfo* method);
typedef int32_t(__stdcall* Screen_get_heightType) (MethodInfo* method);
typedef void* (__stdcall* Singleton_GetInstanceType) (MethodInfo* method);
typedef Il2CppArray* (__stdcall* il2cpp_array_newType) (Il2CppClass* elementTypeInfo, il2cpp_array_size_t length);
typedef struct MethodInfo** (__stdcall* Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfoType) ();
typedef app::Byte__Array* (__fastcall* Unity_RecordUserDataType) (int32_t nType);
typedef Il2CppClass** (__stdcall* GetIl2ClassesType) ();

class GameFunctions
{
public:
	static GameFunctions& GetInstance();
public:
	void InitStaticOffsets();
	app::String* string_to_il2cppi(std::string input);
public:
	Marshal_PtrToStringAnsiType Marshal_PtrToStringAnsi;
	Application_RecordUserDataType Application_RecordUserData;
	GameObject_FindType GameObject_Find;
	GameObject_get_transformType GameObject_get_transform;
	Transform_get_eulerAnglesType Transform_get_eulerAngles;
	Transform_set_eulerAnglesType Transform_set_eulerAngles;
	Input_GetAxisType Input_GetAxis;
	ActorUtils_GetAvatarPosType ActorUtils_GetAvatarPos;
	ActorUtils_SetAvatarPosType ActorUtils_SetAvatarPos;
	Application_get_targetFrameRateType Application_get_targetFrameRate;
	Application_set_targetFrameRateType Application_set_targetFrameRate;
	Cursor_get_visibleType Cursor_get_visible;
	Cursor_set_visibleType Cursor_set_visible;
	Screen_get_widthType Screen_get_width;
	Screen_get_heightType Screen_get_height;
	Singleton_GetInstanceType Singleton_GetInstance;
	il2cpp_array_newType il2cpp_array_new;
	Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfoType Singleton_1_MoleMole_EntityManager__get_Instance__MethodInfo;
	Unity_RecordUserDataType Unity_RecordUserData;
	GetIl2ClassesType GetIl2Classes;

};
