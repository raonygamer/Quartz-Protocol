#pragma once
#include "quartz/utils/Color32.hpp"
#include <array>
#include <cstdint>

namespace quartz::rpc::payloads
{
    template <std::size_t N>
    struct alignas(4) LEDFramebufferSetPayload
    {
        const std::uint32_t MatrixSize = N;
        std::array<utils::Color32, N> Framebuffer = {};
    };
}
