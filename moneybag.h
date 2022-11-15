#ifndef JNP3_MONEYBAG_H
#define JNP3_MONEYBAG_H
#include <algorithm>
#include <cstdint>
#include <ostream>

class Moneybag {

public:
    using coin_number_t = unsigned long;

    // constructors
    explicit constexpr Moneybag(const coin_number_t liv,
                                const coin_number_t sol,
                                const coin_number_t den)
            : livre(liv), solidus(sol), denier(den) {}

    Moneybag(const class Moneybag &mb)
            : livre(mb.livre), solidus(mb.solidus), denier(mb.denier) {}

    // methods


    [[nodiscard]] constexpr coin_number_t livre_number() const {
        return livre;
    }

    constexpr coin_number_t solidus_number() const {
        return solidus;
    }

    [[nodiscard]] constexpr coin_number_t denier_number() const {
        return denier;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Moneybag &lhs);

    // operators

    explicit operator bool() const {
        return livre > 0 || solidus > 0 || denier > 0;
    }

    constexpr inline bool operator==(Moneybag const& b) const {
        return this->livre == b.livre && this->solidus == b.solidus && this->denier == b.denier;
    }

    constexpr inline auto operator<=>(Moneybag const& b) {
        if ((*this) == b) {
            return std::partial_ordering::equivalent;
        }
        if ((this->livre <= b.livre && this->solidus <= b.solidus && this->denier <= b.denier)
            && !((*this) == b)) {
            return std::partial_ordering::less;
        }
        if (this->livre >= b.livre && this->solidus >= b.solidus && this->denier >= b.denier
            && !((*this) == b))  {
            return std::partial_ordering::greater;
        }

        return std::partial_ordering::unordered;
    }

    friend Moneybag operator*(const Moneybag &mb,
                              Moneybag::coin_number_t scalar);

    friend Moneybag operator*(Moneybag::coin_number_t scalar,
                              const Moneybag &mb);

    friend Moneybag operator+(const Moneybag &a, const Moneybag &b);

    friend Moneybag operator-(const Moneybag &a, const Moneybag &b);

    friend Moneybag &operator-=(Moneybag &a, const Moneybag &b);

    friend Moneybag &operator+=(Moneybag &a, const Moneybag &b);

    friend Moneybag &operator*=(Moneybag &mb, const coin_number_t scalar);

private:
    coin_number_t livre, solidus, denier;
};

inline std::ostream &operator<<(std::ostream &stream, const Moneybag &mb) {
    return stream << "(" << mb.livre << " livres, " << mb.solidus
                  << " soliduses, " << mb.denier << " deniers)";
}

constexpr Moneybag Livre(1, 0, 0);
constexpr Moneybag Solidus(0, 1, 0);
constexpr Moneybag Denier(0, 0, 1);

class Value {
public:
    Value(const Moneybag &mb)
            : value(240 * mb.livre_number() + 12 * mb.solidus_number() +
                    mb.denier_number()){};

    Value(Moneybag::coin_number_t denier_number = 0) : value(denier_number){};

    explicit operator std::string() const {
        std::string ret;
        __int128 copy = value;
        while (copy > 0) {
            ret += copy % 10 + '0';
            copy /= 10;
        }

        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    constexpr bool operator==(const Value& rhs) {
        return value == rhs.value;
    }

    constexpr auto operator<=>(const Value& rhs) const = default;

private:
    __int128 value;
};

#endif // JNP3_MONEYBAG_H