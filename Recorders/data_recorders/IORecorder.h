#pragma once
#include "RecorderBase.h"
class IORecorder :
    public RecorderBase
{
    struct PsuedoMouse
    {
        float x;
        float y;
        bool is_inited = false;
    };
public:
    PsuedoMouse m_psuedo_mouse;

public:
    virtual nlohmann::json Record(nlohmann::json record) override;
    virtual void Initialize() override;
};

