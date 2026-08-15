#pragma once
#include "quartz/utils/Alignment.hpp"

namespace quartz::rpc::payloads
{
    enum class CharacteristicType : std::uint8_t
    {
        IncreaseBrightness,
        DecreaseBrightness,
        IncreaseSpeed,
        DecreaseSpeed,
        ChangeMode,
        ChangeDirection
    };

    struct PROTOCOL_ALIGNED ChangeLEDCharacteristicPayload
    {
        CharacteristicType Type;
    };
}