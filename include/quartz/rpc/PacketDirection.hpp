#pragma once
#include <cstdint>

namespace quartz::rpc
{
    enum class PacketDirection : std::uint8_t
    {
        DeviceToHost = 0,
        HostToDevice = 1
    };
}
