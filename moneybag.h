#ifndef JNP3_MONEYBAG_H
#define JNP3_MONEYBAG_H
#include <algorithm>
#include <cstdint>
#include <ostream>

class Moneybag {

    public:
        using coin_number_t = unsigned long;
        static constexpr coin_number_t COIN_NUMBER_MAX = UINT64_MAX;

        explicit constexpr Moneybag(const coin_number_t liv,
                                    const coin_number_t sol,
                                    const coin_number_t den)
                : livre(liv), solidus(sol), denier(den) {}

        [[nodiscard]] constexpr coin_number_t livre_number() const {
            return livre;
        }

        [[nodiscard]] constexpr coin_number_t solidus_number() const {
            return solidus;
        }

        [[nodiscard]] constexpr coin_number_t denier_number() const {
            return denier;
        }

        static void errorReport(const std::string &operation) {
            throw std::out_of_range(
                    "Error: "+ operation + " will cause coin number overflow");
        }

        constexpr explicit operator bool() const {
            return livre > 0 || solidus > 0 || denier > 0;
        }

        constexpr inline bool operator==(Moneybag const &b) const {
            return this->livre == b.livre && this->solidus == b.solidus && this->denier == b.denier;
        }

        constexpr inline auto operator<=>(Moneybag const &b) {
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

        constexpr Moneybag &operator+=(const Moneybag &b) {
            if (COIN_NUMBER_MAX - this->livre < b.livre ||
                COIN_NUMBER_MAX - this->solidus < b.solidus ||
                COIN_NUMBER_MAX - this->denier < b.denier) {
                errorReport("addition");
            }

            this->livre += b.livre;
            this->solidus += b.solidus;
            this->denier += b.denier;

            return (*this);
        }

        constexpr Moneybag operator+(const Moneybag &b) {
            Moneybag mb = (*this);
            mb += b;

            return mb;
        }

        constexpr Moneybag &operator-=(const Moneybag &b) {
            if (this->livre < b.livre || this->solidus < b.solidus || this->denier < b.denier) {
                errorReport("subtraction");
            }

            this->livre += b.livre;
            this->solidus += b.solidus;
            this->denier += b.denier;

            return (*this);
        }

        constexpr Moneybag operator-(const Moneybag &b) {
            Moneybag mb = (*this);
            mb -= b;

            return mb;
        }

        constexpr Moneybag &operator*=(const coin_number_t scalar) {
            if (scalar != 0 && (COIN_NUMBER_MAX / scalar < this->livre ||
                                COIN_NUMBER_MAX / scalar < this->solidus ||
                                COIN_NUMBER_MAX / scalar < this->denier)) {
                errorReport("multiplication");
            }

            this->livre *= scalar;
            this->solidus *= scalar;
            this->denier *= scalar;

            return (*this);
        }

        constexpr Moneybag operator*(const coin_number_t scalar) {
            Moneybag mb2 = (*this);
            return mb2 *= scalar;
        }

    private:
        coin_number_t livre, solidus, denier;
};

constexpr Moneybag operator*(const Moneybag::coin_number_t scalar, const Moneybag &mb) {
    Moneybag mb2 = mb;
    return mb2 *= scalar;
}

inline std::ostream &operator<<(std::ostream &stream, const Moneybag &mb);

inline std::ostream &operator<<(std::ostream &stream, const Moneybag &mb) {
    return stream << "(" << mb.livre_number() << " livres, " << mb.solidus_number()
                  << " soliduses, " << mb.denier_number() << " deniers)";
}

constexpr Moneybag Livre(1, 0, 0);
constexpr Moneybag Solidus(0, 1, 0);
constexpr Moneybag Denier(0, 0, 1);

class Value {
    public:
        Value(const Moneybag & mb): value(240 * mb.livre_number() + 12 * mb.solidus_number() +
                                          mb.denier_number()) {};

        Value(Moneybag::coin_number_t denier_number = 0): value(denier_number) {};

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

        constexpr bool operator==(const Value &rhs) const {
            return value == rhs.value;
        }

        constexpr auto operator<=>(const Value &rhs) const = default;

    private:
        __int128 value;
};

#endif // JNP3_MONEYBAG_H