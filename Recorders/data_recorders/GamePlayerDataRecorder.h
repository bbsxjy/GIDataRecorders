#pragma once
#include "RecorderBase.h"

class GamePlayerDataRecorder :
    public RecorderBase
{
public:
    virtual nlohmann::json Record(nlohmann::json record) override;

};

