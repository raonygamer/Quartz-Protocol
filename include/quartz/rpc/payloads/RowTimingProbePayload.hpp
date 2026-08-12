#pragma once
#include "quartz/utils/Alignment.hpp"
#include <array>

namespace quartz::rpc::payloads
{
    struct PROTOCOL_ALIGNED MatrixTimingProbeRowResult
    {
        std::uint16_t MinTicks = 0;
        std::uint16_t MaxTicks = 0;
        std::uint16_t Samples = 0;
        std::uint8_t Column = 0xFFu;
        std::uint8_t Timeouts = 0;
    };

    static_assert(sizeof(MatrixTimingProbeRowResult) == 8);

    template <std::size_t N>
    struct PROTOCOL_ALIGNED MatrixTimingProbeResult
    {
        std::uint32_t CoreClock = 0;
        std::array<MatrixTimingProbeRowResult, N> Rows {};
    };
}