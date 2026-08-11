#pragma once
#include <array>
#include <cstdint>
#include "quartz/utils/Color32.hpp"

namespace quartz::rpc::payloads
{
    template <std::size_t N>
    struct alignas(4) LEDFramebufferSetPayload
    {
        const std::size_t MatrixSize = N;
        std::array<utils::Color32, N> Framebuffer = {};
    };
}