#pragma once
#include <cstdint>
#include "quartz/utils/Alignment.hpp"

namespace quartz::rpc::payloads
{
    struct PROTOCOL_ALIGNED FirmwareInfoPayload
    {
        const char Version[32];
        const std::uint8_t VersionLength;
    };
}
