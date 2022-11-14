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

void errorReport(const std::string &operation, const coin_number_t &a,
            const coin_number_t &b) {
    throw std::out_of_range(
    "Error: "+ operation + " " + std::to_string(a) + " and " + std::to_string(b)
    + " will cause coin number overflow");
}

Moneybag::operator bool() const {
    return livre > 0 || solidus > 0 || denier > 0;
}

std::ostream &operator<<(std::ostream &stream, const Moneybag &mb) {
    return stream << "(" << mb.livre << " livres, " << mb.solidus
                  << " soliduses, " << mb.denier << " deniers)";
}

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

// TODO: mozna lepszy komunikat bledu - wypisac ktore dodanie nie dziala
Moneybag operator+(const Moneybag &a, const Moneybag &b) {
    if (COIN_NUMBER_MAX - a.livre < b.livre) {
        errorReport("addition", a.livre, b.livre);
    } else if (COIN_NUMBER_MAX - a.solidus < b.solidus) {
        errorReport("addition", a.solidus, b.solidus);
    } else if (COIN_NUMBER_MAX - a.denier < b.denier) {
        errorReport("addition", a.denier, b.denier);
    }

    return Moneybag(a.livre + b.livre, a.solidus + b.solidus,
                    a.denier + b.denier);
}

Moneybag operator-(const Moneybag &a, const Moneybag &b) {
    if (a.livre < b.livre) {
        errorReport("subtraction", a.livre, b.livre);
    } else if (a.solidus < b.solidus) {
        errorReport("subtraction", a.solidus, b.solidus);
    } else if (a.denier < b.denier) {
        errorReport("subtraction", a.denier, b.denier);
    }

    return Moneybag(a.livre - b.livre, a.solidus - b.solidus,
                    a.denier - b.denier);
}

Moneybag operator*(const Moneybag &mb, coin_number_t scalar) {
    if (COIN_NUMBER_MAX / scalar < mb.livre ||
        COIN_NUMBER_MAX / scalar < mb.solidus ||
        COIN_NUMBER_MAX / scalar < mb.denier) {
        throw std::out_of_range(
                "Error: multiplication will cause coin number overflow");
    }
    //TODO nie jestem pewna odnośnie uzycia NULL
//    if (COIN_NUMBER_MAX / scalar <  mb.livre) {
//        errorReport("multiplication", mb.livre, NULL);
//    } else if (COIN_NUMBER_MAX / scalar < mb.solidus) {
//        errorReport("multiplication", mb.solidus, NULL);
//    } else if (COIN_NUMBER_MAX / scalar < mb.denier) {
//        errorReport("multiplication", mb.denier, NULL);
//    }

    return Moneybag(mb.livre * scalar, mb.solidus * scalar, mb.denier * scalar);
}

Moneybag operator*(coin_number_t scalar, const Moneybag &mb) {
    return mb * scalar;
}

// TODO: uzywanie move, nie wiem czy tak jest wydajnie

Moneybag &operator+=(Moneybag &a, const Moneybag &b) {
    if (COIN_NUMBER_MAX - a.livre < b.livre) {
        errorReport("addition", a.livre, b.livre);
    } else if (COIN_NUMBER_MAX - a.solidus < b.solidus) {
        errorReport("addition", a.solidus, b.solidus);
    } else if (COIN_NUMBER_MAX - a.denier < b.denier) {
        errorReport("addition", a.denier, b.denier);
    }

    a.livre += b.livre;
    a.solidus += b.solidus;
    a.denier += b.denier;

    return a;
}

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