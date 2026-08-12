#pragma once
#include <cstdint>
#include "quartz/utils/Alignment.hpp"

namespace quartz::rpc::payloads
{
    struct PROTOCOL_ALIGNED PerformancePayload
    {
        /// Always at 48 MHz
        const std::uint32_t CoreClock = 48'000'000;
        std::uint32_t BeginScanTicks = 0;
        std::uint32_t ScanTicks = 0;
        std::uint32_t EndScanTicks = 0;
        std::uint32_t StateUpdateTicks = 0;
        std::uint32_t HIDTicks = 0;
        std::uint32_t RGBTicks = 0;
        std::uint32_t AverageScanPeriodTicks = 0;
        std::uint32_t RGBSlotMaxTicks = 0;
    };

    static_assert(sizeof(PerformancePayload) == 36, "PerformancePayload should be 36 bytes!");
}