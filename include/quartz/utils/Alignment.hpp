#pragma once
#include <cstdint>

namespace quartz::rpc
{
    inline constexpr std::uint32_t ALIGN_SIZE = sizeof(std::uint32_t);
}

#define PROTOCOL_ALIGNED alignas(ALIGN_SIZE)