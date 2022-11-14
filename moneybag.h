#ifndef JNP3_MONEYBAG_H
#define JNP3_MONEYBAG_H

#include <cstdint>
#include <ostream>

class Moneybag {
public:
    using coin_number_t = unsigned long;

    explicit constexpr Moneybag(const coin_number_t liv,
                                const coin_number_t sol,
                                const coin_number_t den)
            : livre(liv), solidus(sol), denier(den) {}

   [[nodiscard]] constexpr coin_number_t livre_number() const;

    [[nodiscard]] constexpr coin_number_t solidus_number() const;

    [[nodiscard]] constexpr coin_number_t denier_number() const;

    constexpr std::ostream &operator<<(std::ostream &stream, const Moneybag &lhs);

    explicit operator bool() const;

    constexpr inline bool operator==(const Moneybag &a, const Moneybag &b);

    constexpr inline bool operator<(const Moneybag &a, const Moneybag &b);

    constexpr inline bool operator<=(const Moneybag &a, const Moneybag &b);

    constexpr inline bool operator>(const Moneybag &a, const Moneybag &b);

    constexpr inline bool operator>=(const Moneybag &a, const Moneybag &b);

    constexpr inline Moneybag operator*(const Moneybag &mb,
                              Moneybag::coin_number_t scalar);

    constexpr inline Moneybag operator*(Moneybag::coin_number_t scalar,
                              const Moneybag &mb);

    constexpr inline Moneybag operator+(const Moneybag &a, const Moneybag &b);

    constexpr inline Moneybag operator-(const Moneybag &a, const Moneybag &b);

    constexpr inline Moneybag &operator+=(Moneybag &a, const Moneybag &b);

private:
    coin_number_t livre, solidus, denier;
};

constinit const Moneybag Livre(1, 0, 0);
constinit const Moneybag Solidus(0, 1, 0);
constinit const Moneybag Denier(0, 0, 1);

class Value {
public:
    using coin_number_t = Moneybag::coin_number_t;

    Value() : livre(0), solidus(0), denier(0) {}

    explicit Value(const Moneybag &mb)
            : livre(mb.livre_number()), solidus(mb.solidus_number()),
              denier(mb.denier_number()) {
        normalize();
    }

    Value(coin_number_t denier_number) : livre(0), solidus(0), denier(denier_number) {
        normalize();
    }

    Value(const class Value &v)
            : livre(v.livre), solidus(v.solidus), denier(v.denier) {}

    auto operator<=>(const Value &) const = default;

private:
    coin_number_t livre, solidus, denier;

    void normalize();
};

#endif // JNP3_MONEYBAG_H