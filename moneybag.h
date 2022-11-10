//
// Created by acer on 09.11.22.
//

#ifndef JNP3_MONEYBAG_H
#define JNP3_MONEYBAG_H
#include <cstdint>
#include <ostream>


class Solidus {
    using coin_number_t =  unsigned long long;

    public:
        coin_number_t solidus_num;

        explicit Solidus(const coin_number_t coins)
                : solidus_num(coins) {
        }
};

class Denier {
    using coin_number_t =  unsigned long long;

    public:
        coin_number_t denier_num;

        explicit Denier(const coin_number_t coins)
                : denier_num(coins) {
        }
};

class Livre {
    using coin_number_t =  unsigned long long;

    public:
        coin_number_t livre_num;

        explicit Livre(const coin_number_t coins)
            : livre_num(coins) {
        }
};

class Moneybag {

    public:
        using coin_number_t =  unsigned long long;

        //constructors
        explicit Moneybag(const coin_number_t liv, const coin_number_t sol
                          , const coin_number_t den)
                          : livre(liv), solidus(sol), denier(den) {
        }

        // TODO Konstruktor do livre, solidus, denier ???
        Moneybag(const class Moneybag &mb)
                : livre(mb.livre), solidus(mb.solidus), denier(mb.denier){
        }

        //methods

        [[nodiscard]] coin_number_t livre_number() const;

        [[nodiscard]] coin_number_t solidus_number () const;

        [[nodiscard]] coin_number_t denier_number() const;

        Moneybag operator+(const Moneybag &mb) const;

        friend std::ostream &operator<<(std::ostream &stream, const Moneybag &lhs);

        //operators

        explicit operator bool() const;
        
        friend bool operator==(const Moneybag &a, const Moneybag &b);

        friend bool operator<(const Moneybag &a, const Moneybag &b);

        friend bool operator<=(const Moneybag &a, const Moneybag &b);
        
        friend bool operator>(const Moneybag &a, const Moneybag &b);
        
        friend bool operator>=(const Moneybag &a, const Moneybag &b);

    private:
         Livre livre;

         Solidus solidus;

         Denier denier;

         static coin_number_t all_coins_in_den_number(const Moneybag &mb) ;
};

#endif //JNP3_MONEYBAG_H
