#pragma once
#include <cstdint>
#include <span>

#include "PacketDirection.hpp"
#include "PacketType.hpp"

namespace quartz::rpc
{
    struct alignas(4) PacketHeader
    {
        static constexpr std::uint32_t MAGIC_NUMBER = 0x43505251u; // "QRPC"
        std::uint32_t Magic;
        std::uint8_t Version;
        PacketType Type;
        PacketDirection Direction;
        std::uint32_t PayloadLength;

        static constexpr bool isValidHeader(const std::span<const std::byte> buff) noexcept
        {
            if (buff.size() < sizeof(PacketHeader))
                return false;
            const auto& header = *reinterpret_cast<const PacketHeader*>(buff.data());
            if (header.Magic != MAGIC_NUMBER)
                return false;
            if (header.Type == PacketType::Invalid || header.Type == PacketType::Error)
                return false;
            return true;
        }

        template <typename T>
        T* getPayload() noexcept
        {
            static_assert(std::is_trivially_copyable_v<T>);
            static_assert(alignof(T) <= alignof(PacketHeader));
            auto* base = reinterpret_cast<std::byte*>(this) + sizeof(PacketHeader);
            if (PayloadLength < sizeof(T))
                return nullptr;
            return reinterpret_cast<T*>(base);
        }

        template <typename T>
        const T* getPayload() const noexcept
        {
            static_assert(std::is_trivially_copyable_v<T>);
            static_assert(alignof(T) <= alignof(PacketHeader));
            const auto* base = reinterpret_cast<const std::byte*>(this) + sizeof(PacketHeader);
            if (PayloadLength < sizeof(T))
                return nullptr;
            return reinterpret_cast<const T*>(base);
        }
    };

    static_assert(sizeof(PacketHeader) == 16, "PacketHeader must be 16 bytes!");
}