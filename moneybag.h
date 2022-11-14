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