
#include <iostream>
#include <ranges>
#include <span>
#include <filesystem>
#include <cstdint>

inline namespace aux
{
    struct unicursal {
        int64_t x;
        int64_t y;
        int64_t z;
        constexpr bool operator==(unicursal const& rhs) const noexcept {
            return this->x * rhs.z == rhs.x * this->z
                && this->y * rhs.z == rhs.y * this->z;
        }
        constexpr auto cross(unicursal const& rhs) const noexcept {
            return unicursal{
                this->y * rhs.z - this->z * rhs.y,
                this->z * rhs.x - this->x * rhs.z,
                this->x * rhs.y - this->y * rhs.x,
            };
        }
        constexpr friend auto cross(unicursal const& lhs, unicursal const& rhs) noexcept {
            return lhs.cross(rhs);
        }
        friend auto& operator<<(std::ostream& output, unicursal const& u) noexcept {
            return output << '(' << u.x << ' ' << u.y << ' ' << u.z << ')';
        }
    };
} // ::aux

int main(int argc, char const** argv) {
    auto args = std::span<char const*>(argv, argc)
        | std::views::filter([](auto x) { return std::filesystem::exists(x); })
        | std::views::transform([](auto x) { return std::filesystem::canonical(x); });
    for (auto item : args) {
        std::cout << item.c_str() << std::endl;
    }
    constexpr unicursal a(-1,-1,+1);
    constexpr unicursal b(+2,-1,+1);
    constexpr unicursal c(+2,+2,+1);
    constexpr unicursal d(-1,+2,+1);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << std::endl;

    constexpr auto ab_(cross(a, b));
    constexpr auto cd_(cross(c, d));
    constexpr auto da_(cross(d, a));
    constexpr auto bc_(cross(b, c));
    constexpr auto ac_(cross(a, c));
    constexpr auto db_(cross(d, b));
    std::cout << ab_ << std::endl;
    std::cout << cd_ << std::endl;
    std::cout << da_ << std::endl;
    std::cout << bc_ << std::endl;
    std::cout << ac_ << std::endl;
    std::cout << db_ << std::endl;
    std::cout << std::endl;

    constexpr auto ab_cd__(cross(ab_, cd_));
    constexpr auto da_bc__(cross(da_, bc_));
    std::cout << ab_cd__ << std::endl;
    std::cout << da_bc__ << std::endl;
    std::cout << std::endl;

    constexpr auto ab_cd__da_bc___(cross(ab_cd__, da_bc__));
    std::cout << ab_cd__da_bc___  << std::endl;
    std::cout << std::endl;

    constexpr auto ab_cd__da_bc___ac__(cross(ab_cd__da_bc___, ac_));
    constexpr auto ab_cd__da_bc___db__(cross(ab_cd__da_bc___, db_));
    std::cout << ab_cd__da_bc___ac__ << std::endl;
    std::cout << ab_cd__da_bc___db__ << std::endl;

    return 0;
}
