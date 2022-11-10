#include "moneybag.h"
using coin_number_t =  unsigned long long;

coin_number_t Moneybag::all_coins_in_den_number
        (const Moneybag &mb) {
    return mb.denier_number() + mb.solidus_number() * 12 +
           mb.livre_number() * 240;
}

coin_number_t Moneybag::livre_number() const {
    return livre.livre_num;
}

coin_number_t Moneybag::solidus_number() const{
    return solidus.solidus_num;
}

coin_number_t Moneybag::denier_number() const {
    return denier.denier_num;
}

Moneybag::operator bool() const {
    return  livre_number() > 0 || solidus_number() > 0 || denier_number() > 0 ;
}

std::ostream &operator<<(std::ostream &stream, const Moneybag &mb) {
    return stream << "(" << mb.livre_number() << " livres, "
                << mb.solidus_number() << " soliduses, " << mb.denier_number()
                << " deniers)";
}

bool operator==(const Moneybag &a, const Moneybag &b) {
    return  a.livre_number() == b.livre_number()
            && a.solidus_number() == b.solidus_number()
            && a.denier_number() == b.denier_number();
}


bool operator<=(const Moneybag &a, const Moneybag &b) {
    return a.livre_number() <= b.livre_number()
           && a.solidus_number() <= b.solidus_number()
           && a.denier_number() <= b.denier_number();
}

bool operator<(const Moneybag &a, const Moneybag &b) {
    return a <= b && !(a == b);
}

bool operator>=(const Moneybag &a, const Moneybag &b) {
    return a.livre_number() >= b.livre_number()
           && a.solidus_number() >= b.solidus_number()
           && a.denier_number() >= b.denier_number();
}

bool operator>(const Moneybag &a, const Moneybag &b) {
    return a >= b && !(a == b);
}

Moneybag Moneybag::operator+(const Moneybag &mb) const {
    // TODO
    return Moneybag(0, 0, 0);
}


