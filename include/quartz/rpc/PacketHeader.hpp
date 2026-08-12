#pragma once
#include <cstdint>
#include <span>
#include "quartz/rpc/PacketDirection.hpp"
#include "quartz/rpc/PacketType.hpp"
#include "quartz/utils/Alignment.hpp"

#define ENFORCE_PROPERLY_ALIGNED(T) static_assert(alignof(T) <= ALIGN_SIZE)
namespace quartz::rpc
{
    struct PROTOCOL_ALIGNED PacketHeader
    {
    private:
        inline static std::uint32_t _NextPacketId = 0;
        constexpr PacketHeader(
            const std::uint8_t version,
            const PacketType type,
            const PacketDirection direction,
            const std::uint32_t packetId,
            const std::uint32_t responseFor,
            const std::uint32_t payloadLength
        ) noexcept :
            Version(version),
            Type(type),
            Direction(direction),
            PacketId(packetId),
            ResponseFor(responseFor),
            PayloadLength(payloadLength)
        {
        }

    public:
        static constexpr std::uint32_t MAGIC_NUMBER = 0x43505251u; // "QRPC"
        const std::uint32_t Magic = MAGIC_NUMBER;
        const std::uint8_t Version = 1;
        const PacketType Type = PacketType::Invalid;
        const PacketDirection Direction = PacketDirection::DeviceToHost;
        std::uint32_t PacketId = 0;
        std::uint32_t ResponseFor = 0;
        std::uint32_t PayloadLength = 0;

        constexpr PacketHeader() noexcept = default;
        constexpr PacketHeader(
            const std::uint8_t version,
            const PacketType type,
            const PacketDirection direction,
            const std::uint32_t responseFor,
            const std::uint32_t payloadLength = 0
        ) noexcept :
            Version(version),
            Type(type),
            Direction(direction),
            ResponseFor(responseFor),
            PayloadLength(payloadLength)
        {
            PacketId = getNextPacketId();
        }

        static PacketHeader deserialize(const std::span<const std::byte> buff) noexcept
        {
            if (!isValidHeader(buff))
                return {};
            return PacketHeader(
                *reinterpret_cast<const std::uint8_t*>(buff.data() + offsetof(PacketHeader, Version)),
                *reinterpret_cast<const PacketType*>(buff.data() + offsetof(PacketHeader, Type)),
                *reinterpret_cast<const PacketDirection*>(buff.data() + offsetof(PacketHeader, Direction)),
                *reinterpret_cast<const std::uint32_t*>(buff.data() + offsetof(PacketHeader, PacketId)),
                *reinterpret_cast<const std::uint32_t*>(buff.data() + offsetof(PacketHeader, ResponseFor)),
                *reinterpret_cast<const std::uint32_t*>(buff.data() + offsetof(PacketHeader, PayloadLength))
            );
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
            if (header.PacketId == 0)
                return false;
            return true;
        }

        template <typename T>
        constexpr bool isSamePayloadSize() const noexcept
        {
            static_assert(std::is_trivially_copyable_v<T>);
            ENFORCE_PROPERLY_ALIGNED(T);
            return PayloadLength == sizeof(T);
        }

        template <typename T>
        T* getPayload() noexcept
        {
            static_assert(std::is_trivially_copyable_v<T>);
            ENFORCE_PROPERLY_ALIGNED(T);
            auto* base = reinterpret_cast<std::byte*>(this) + sizeof(PacketHeader);
            if (PayloadLength != sizeof(T))
                return nullptr;
            return reinterpret_cast<T*>(base);
        }

        template <typename T>
        const T* getPayload() const noexcept
        {
            static_assert(std::is_trivially_copyable_v<T>);
            ENFORCE_PROPERLY_ALIGNED(T);
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
            return isValidHeader(std::as_bytes(std::span{ this, 1 }));
        }

        static std::uint32_t getNextPacketId() noexcept
        {
            if (++_NextPacketId == 0) ++_NextPacketId;
            return _NextPacketId;
        }
    };

    static_assert(alignof(PacketHeader) == ALIGN_SIZE);
    static_assert(sizeof(PacketHeader) % ALIGN_SIZE == 0);
    static_assert(sizeof(PacketHeader) == 24, "PacketHeader must be 24 bytes!");
}
#undef ENFORCE_PROPERLY_ALIGNED