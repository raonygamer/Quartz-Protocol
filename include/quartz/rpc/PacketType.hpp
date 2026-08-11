#pragma once
#include <cstdint>

namespace quartz::rpc
{
    enum class PacketType : std::uint16_t
    {
        Invalid = 0,
        Ping = 1,
        Pong = 2,
        PerformanceRequest = 3,
        PerformanceResponse = 4,
        LEDFramebufferSet = 5,
        Error = 0xFFFFu
    };
}
