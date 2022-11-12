#pragma once
using namespace app;
//For YuanShen v3.2
#define DO_UNITY_APP_FUNC(a, r, n, p) r (*n) p
#define UNITY_RECORD_USER_DATA_OFFSET 0x00BA4D80

//ImageBase = UnityPlayer.dll
DO_UNITY_APP_FUNC(0x00BA4D80, app::Byte__Array*, Unity_RecordUserData, (int32_t nType));
DO_UNITY_APP_FUNC(0x00B41920, Il2CppClass**, GetIl2Classes, ());
