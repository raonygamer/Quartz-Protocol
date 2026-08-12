#pragma once
#include <array>
#include <cstdint>
#include "quartz/utils/Color32.hpp"
#include "quartz/utils/Alignment.hpp"

namespace quartz::rpc::payloads
{
    template <std::size_t N>
    struct PROTOCOL_ALIGNED FramebufferSetPayload
    {
        const std::uint32_t MatrixSize = N;
        std::array<utils::Color32, N> Framebuffer = {};
    };
}
