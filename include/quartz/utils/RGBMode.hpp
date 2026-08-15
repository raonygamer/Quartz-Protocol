#pragma once
#include <cstdint>

namespace quartz::utils
{
    enum class RGBMode : std::uint8_t
    {
        Direct = 0,
        Firmware = 1
    };
}