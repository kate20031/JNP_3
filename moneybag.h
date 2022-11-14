#ifndef JNP3_MONEYBAG_H
#define JNP3_MONEYBAG_H
#include <algorithm>
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