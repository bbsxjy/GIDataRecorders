#pragma once
#include "RecorderBase.h"
#include "GamePlayerDataRecorder.h"
#include "GameWorldVarsRecorder.h"
#include "IORecorder.h"
#include "VideoRecorder.h"
class RecorderMain :
    public RecorderBase
{
public:
    GamePlayerDataRecorder* m_gpdr;
    GameWorldVarsRecorder* m_gwvr;
    IORecorder* m_ior;
    VideoRecorder* m_vr;
    bool m_is_interrupted = true;
    bool m_is_in_game = false;
public:
    void Init();
    void Run();
};

