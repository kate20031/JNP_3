#ifndef JNP3_MONEYBAG_H
#define JNP3_MONEYBAG_H
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

    [[nodiscard]] coin_number_t livre_number() const;

    [[nodiscard]] coin_number_t solidus_number() const;

    [[nodiscard]] coin_number_t denier_number() const;

    friend std::ostream &operator<<(std::ostream &stream, const Moneybag &lhs);

    // operators

    explicit operator bool() const;

    friend bool operator==(const Moneybag &a, const Moneybag &b);

    friend bool operator<(const Moneybag &a, const Moneybag &b);

    friend bool operator<=(const Moneybag &a, const Moneybag &b);

    friend bool operator>(const Moneybag &a, const Moneybag &b);

    friend bool operator>=(const Moneybag &a, const Moneybag &b);

    friend Moneybag operator*(const Moneybag &mb,
                              Moneybag::coin_number_t scalar);

    friend Moneybag operator*(Moneybag::coin_number_t scalar,
                              const Moneybag &mb);

    friend Moneybag operator+(const Moneybag &a, const Moneybag &b);

    friend Moneybag operator-(const Moneybag &a, const Moneybag &b);

    friend Moneybag &operator+=(Moneybag &a, const Moneybag &b);

private:
    coin_number_t livre, solidus, denier;
};

constexpr Moneybag Livre(1, 0, 0);
constexpr Moneybag Solidus(0, 1, 0);
constexpr Moneybag Denier(0, 0, 1);

class Value {

public:
    using coin_number_t = Moneybag::coin_number_t;

    Value() : livre(0), solidus(0), denier(0) {}

    Value(const Moneybag &mb)
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