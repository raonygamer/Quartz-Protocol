#pragma once
#include <cstdint>

namespace quartz::utils
{
    struct Color32
    {
        std::uint8_t R;
        std::uint8_t G;
        std::uint8_t B;

        static constexpr bool equals(const Color32& a, const Color32& b) noexcept
        {
            return a.R == b.R && a.G == b.G && a.B == b.B;
        }

        constexpr bool equals(const Color32& other) const noexcept
        {
            return equals(*this, other);
        }

        constexpr bool operator==(const Color32& other) const noexcept
        {
            return this->equals(other);
        }

        constexpr bool operator!=(const Color32& other) const noexcept
        {
            return !this->equals(other);
        }
    };
}