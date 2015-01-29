#include <vector>
#include <string>
#include <locale>
#include <cmath>
#include <ostream>

#include "vmanip.h++"
#include "bigcub.h++"

// Constructors

BigCub::BigCub(void) {
    
}

BigCub::BigCub(BigCub const &n) {
    *this = n;
}

BigCub::BigCub(Type const &n) {
    data = std::vector<bool>(n);
    vmanip::compress(data);
}

BigCub::BigCub(char const *str) {
//    if (str == NULL || str[0] == '\0') {
//        return;
//    }
//    
//    bool negative = false;
//    
//    if (str[0] == '-') {
//        negative = true;
//    }
//    
//    size_t strSize = std::strlen(str);
//    str = str + (strSize - 1);
//    for (size_t i = 1; i <= strSize; ++i, --str) {
//        if (std::isdigit(*str)) { // FIXME: oh god this is horrible pls fix
//            *this += (*str - '0') * static_cast<uintmax_t>(std::pow(10, i - 1));
//        }
//	}
//    
//    if (negative) {
//        vmanip::invert(data);
//    }
}

BigCub::BigCub(std::string const &str) : BigCub(str.c_str()) {
    
}

// Destructor

BigCub::~BigCub() {
    
}

// Internal data access related operators

BigCub::Type::reference BigCub::operator[](size_type n) {
    return data[n];
}

BigCub::Type::const_reference const BigCub::operator[](size_type n) const {
    return data[n];
}

BigCub::Type::reference BigCub::at(size_type n) {
    return data.at(n);
}

BigCub::Type::const_reference const BigCub::at(size_type n) const {
    return data.at(n);
}

BigCub::Type &BigCub::operator*() {
    return data;
}

BigCub::Type const &BigCub::operator*() const {
    return data;
}

BigCub::size_type BigCub::size() const {
    return data.size();
}

// Assignation operators

BigCub &BigCub::operator=(BigCub const &n) {
    data = std::vector<bool>(n.data);
    vmanip::compress(data);
    
    return *this;
}

BigCub &BigCub::operator+=(BigCub const &n) {
    vmanip::add(data, n.data, data);
    return *this;
}

BigCub &BigCub::operator-=(BigCub const &n) {
    Type invertedOther = n.data;
    vmanip::invert(invertedOther);
    vmanip::add(data, invertedOther, data);
    return *this;
}

BigCub &BigCub::operator&=(BigCub const &n) {
    vmanip::transform(data, n.data, data, std::bit_and<bool>());
    return *this;
}

BigCub &BigCub::operator|=(BigCub const &n) {
    vmanip::transform(data, n.data, data, std::bit_or<bool>());
    return *this;
}

BigCub &BigCub::operator^=(BigCub const &n) {
   vmanip::transform(data, n.data, data, std::bit_xor<bool>());
    return *this;
}

BigCub &BigCub::operator<<=(size_type const &n) {
    if (n > data.size()) {
        vmanip::transform(data, [](){return false;});
    }
    else {
        data.erase(data.end() - n, data.end());
        data.insert(data.begin(), n, false);
    }
    
    vmanip::compress(data);
    
    return *this;
}

BigCub &BigCub::operator>>=(size_type const &n) {
    if (n > data.size()) {
        vmanip::transform(data, [this](){return this->data.back();});
    }
    else {
        data.erase(data.end() - n, data.end());
        data.insert(data.begin(), n, false);
    }
    
    vmanip::compress(data);
    
    return *this;
}

// Arithmetic operators

BigCub BigCub::operator+(BigCub const &n) const {
	BigCub toReturn(*this);
    toReturn += n;
    
    return toReturn;
}

BigCub BigCub::operator-(BigCub const &n) const {
    BigCub toReturn(*this);
    toReturn -= n;
    
    return toReturn;
}

BigCub BigCub::operator-() const {
    BigCub toReturn(*this);
    vmanip::invert(toReturn.data);
    
    return toReturn;
}

BigCub &BigCub::operator++() {
    Type one = {true, false};
    vmanip::add(data, one, data);
    
    return *this;
}

BigCub BigCub::operator++(int) {
    BigCub toReturn(*this);
    ++toReturn;
    
    return toReturn;
}

BigCub &BigCub::operator--() {
    Type one = {true, true};
    vmanip::add(data, one, data);
    
    return *this;
}

BigCub BigCub::operator--(int) {
    BigCub toReturn(*this);
    --toReturn;
    
    return toReturn;
}

// Comparaison operators

bool BigCub::operator==(BigCub const &n) const {
    return vmanip::compare(data, n.data) == 0;
}

bool BigCub::operator!=(BigCub const &n) const {
    return vmanip::compare(data, n.data) != 0;
}

bool BigCub::operator<(BigCub const &n) const {
    return vmanip::compare(data, n.data) < 0;
}

bool BigCub::operator>(BigCub const &n) const {
    return vmanip::compare(data, n.data) > 0;
}

bool BigCub::operator<=(BigCub const &n) const {
    return vmanip::compare(data, n.data) <= 0;
}

bool BigCub::operator>=(BigCub const &n) const {
    return vmanip::compare(data, n.data) >= 0;
}

// Bitwise operators

BigCub BigCub::operator&(BigCub const &n) const {
    BigCub toReturn(*this);
    toReturn &= n;
    return toReturn;
}

BigCub BigCub::operator|(BigCub const &n) const {
    BigCub toReturn(*this);
    toReturn |= n;
    
    return toReturn;
}

BigCub BigCub::operator^(BigCub const &n) const {
    BigCub toReturn(*this);
    toReturn ^= n;
    
    return toReturn;
}

BigCub BigCub::operator<<(size_type const &n) const {
    BigCub toReturn(*this);
    toReturn <<= n;
    
    return toReturn;
}

BigCub BigCub::operator>>(size_type const &n) const {
    BigCub toReturn(*this);
    toReturn >>= n;
    
    return toReturn;
}

BigCub BigCub::operator~() const {
    BigCub toReturn(*this);
    toReturn.data.flip();
    
    return toReturn;
}

// std::cout overload

std::ostream &operator<<(std::ostream &o, BigCub const &n) {
    o << static_cast<intmax_t>(n);
    
    return o;
}

