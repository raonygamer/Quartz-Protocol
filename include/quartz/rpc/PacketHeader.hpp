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
        std::uint32_t Magic = MAGIC_NUMBER;
        std::uint8_t Version = 1;
        PacketType Type = PacketType::Invalid;
        PacketDirection Direction = PacketDirection::DeviceToHost;
        std::uint32_t PayloadLength = 0;

        constexpr PacketHeader() noexcept = default;
        constexpr PacketHeader(const std::uint8_t version, const PacketType type, const PacketDirection direction,
                               const std::uint32_t payloadLength = 0) noexcept
        {
            this->Version = version;
            this->Type = type;
            this->Direction = direction;
            this->PayloadLength = payloadLength;
        }

        static PacketHeader deserialize(const std::span<const std::byte> buff) noexcept
        {
            PacketHeader header = {};
            if (!isValidHeader(buff))
                return header;
            header.Version = *reinterpret_cast<const std::uint8_t*>(buff.data() + offsetof(PacketHeader, Version));
            header.Type = *reinterpret_cast<const PacketType*>(buff.data() + offsetof(PacketHeader, Type));
            header.Direction = *reinterpret_cast<const PacketDirection*>(buff.data() +
                                                                         offsetof(PacketHeader, Direction));
            header.PayloadLength = *reinterpret_cast<const std::uint32_t*>(buff.data() + offsetof(
                                                                                             PacketHeader, PayloadLength));
            return header;
        }

        static const PacketHeader* asPtr(const std::span<const std::byte> buff) noexcept
        {
            if (!isValidHeader(buff))
                return nullptr;
            return reinterpret_cast<const PacketHeader*>(buff.data());
        }

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
        constexpr bool isSamePayloadSize() const noexcept
        {
            static_assert(std::is_trivially_copyable_v<T>);
            static_assert(alignof(T) <= alignof(PacketHeader));
            return PayloadLength == sizeof(T);
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
            if (PayloadLength != sizeof(T))
                return nullptr;
            return reinterpret_cast<const T*>(base);
        }

        constexpr bool isDeviceToHost() const noexcept
        {
            return Direction == PacketDirection::DeviceToHost;
        }

        constexpr bool isHostToDevice() const noexcept
        {
            return Direction == PacketDirection::HostToDevice;
        }

        constexpr bool isValid() const noexcept
        {
            return isValidHeader(std::as_bytes(std::span{this, 1}));
        }
    };

    static_assert(sizeof(PacketHeader) == 16, "PacketHeader must be 16 bytes!");
}