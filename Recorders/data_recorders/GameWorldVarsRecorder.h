#pragma once
#include "RecorderBase.h"
class GameWorldVarsRecorder :
    public RecorderBase
{
public:
    virtual nlohmann::json Record(nlohmann::json record) override;
};

