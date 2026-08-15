#pragma once
#include "quartz/utils/Alignment.hpp"
#include "quartz/utils/RGBMode.hpp"

namespace quartz::rpc::payloads
{
    struct PROTOCOL_ALIGNED ChangeFirmwareRGBModePayload
    {
        utils::RGBMode Mode;
    };
}