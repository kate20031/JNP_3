#include "moneybag.h"

using coin_number_t = Moneybag::coin_number_t;

constexpr coin_number_t COIN_NUMBER_MAX = UINT64_MAX;

coin_number_t Moneybag::livre_number() const {
    return livre;
}

coin_number_t Moneybag::solidus_number() const {
    return solidus;
}

coin_number_t Moneybag::denier_number() const {
    return denier;
}

void errorReport(const std::string &operation) {
            throw std::out_of_range(
    "Error: "+ operation + " will cause coin number overflow");
}

Moneybag::operator bool() const {
    return livre > 0 || solidus > 0 || denier > 0;
}

std::ostream &operator<<(std::ostream &stream, const Moneybag &mb) {
    return stream << "(" << mb.livre << " livres, " << mb.solidus
                  << " soliduses, " << mb.denier << " deniers)";
}

// TODO Change to operator<=>
bool operator==(const Moneybag &a, const Moneybag &b) {
    return a.livre == b.livre && a.solidus == b.solidus && a.denier == b.denier;
}

bool operator<=(const Moneybag &a, const Moneybag &b) {
    return a.livre <= b.livre && a.solidus <= b.solidus && a.denier <= b.denier;
}

bool operator<(const Moneybag &a, const Moneybag &b) {
    return a <= b && !(a == b);
}

bool operator>=(const Moneybag &a, const Moneybag &b) {
    return a.livre >= b.livre && a.solidus >= b.solidus && a.denier >= b.denier;
}

bool operator>(const Moneybag &a, const Moneybag &b) {
    return a >= b && !(a == b);
}

// TODO: uzywanie move, nie wiem czy tak jest wydajenie

Moneybag &operator+=(Moneybag &a, const Moneybag &b) {
    if (COIN_NUMBER_MAX - a.livre < b.livre ||
        COIN_NUMBER_MAX - a.solidus < b.solidus ||
        COIN_NUMBER_MAX - a.denier < b.denier) {
        errorReport("addition");
    }

    a.livre += b.livre;
    a.solidus += b.solidus;
    a.denier += b.denier;

    return a;
}

Moneybag operator+(const Moneybag &a, const Moneybag &b) {
    Moneybag mb = a;
    mb += b;

    return mb;
}

Moneybag operator-(const Moneybag &a, const Moneybag &b) {
    if (a.livre < b.livre || a.solidus < b.solidus || a.denier < b.denier) {
        errorReport("subtraction");
    }

    return Moneybag(a.livre - b.livre, a.solidus - b.solidus,
                    a.denier - b.denier);
}


// TODO use function *= ???
Moneybag operator*(const Moneybag &mb, const coin_number_t scalar) {
    if (COIN_NUMBER_MAX / scalar < mb.livre ||
        COIN_NUMBER_MAX / scalar < mb.solidus ||
        COIN_NUMBER_MAX / scalar < mb.denier) {
        errorReport("multiplication");
    }

    return Moneybag(mb.livre * scalar, mb.solidus * scalar, mb.denier * scalar);
}

// TODO use function *=
Moneybag operator*(const coin_number_t scalar, const Moneybag &mb) {
    return mb * scalar;
}


// TODO change
void Value::normalize() {
    // TODO: magiczne stale
    coin_number_t denier_to_solidus = denier / 12;
    coin_number_t actual_denier_to_solidus =
            std::min(denier_to_solidus, COIN_NUMBER_MAX - solidus);
    denier -= actual_denier_to_solidus * 12;
    solidus += actual_denier_to_solidus;

    coin_number_t solidus_to_livre = solidus / 20;
    coin_number_t actual_solidus_to_livre =
            std::min(solidus_to_livre, COIN_NUMBER_MAX - livre);
    solidus -= actual_solidus_to_livre * 20;
    livre += actual_solidus_to_livre;
}