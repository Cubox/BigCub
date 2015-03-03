#include <vector>
#include <string>
#include <locale>
#include <cmath>
#include <ostream>

#include "vmanip.h++"
#include "bigcub.h++"

// Constructors

BigCub::BigCub(Type const &n) {
    data = std::vector<bool>(n);
}

BigCub::BigCub(Type &&n) {
    data = n;
}

BigCub::BigCub(char const *str) {
   if (str == NULL || str[0] == '\0') {
       return;
   }
   
   bool negative = false;
   if (str[0] == '-') {
       negative = true;
   }
   
   size_t strSize = std::strlen(str);
   for (size_t i = 0; i < strSize; ++i) {
       if (std::isdigit(str[i])) {
           *this *= 10;
           *this += str[i] - '0';
       }
	}
   
   if (negative) {
       vmanip::invert(data);
   }
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

BigCub::Type::const_reference BigCub::operator[](size_type n) const {
    return data[n];
}

BigCub::Type::reference BigCub::at(size_type n) {
    return data.at(n);
}

BigCub::Type::const_reference BigCub::at(size_type n) const {
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

void BigCub::compress() {
    vmanip::compress(data, 0);
}

// Assignation operators

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

BigCub &BigCub::operator*=(BigCub const &n) {
    vmanip::mul(data, n.data, data);
    
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

BigCub &BigCub::operator<<=(size_type const n) {
    vmanip::lshift(data, n);

    return *this;
}

BigCub &BigCub::operator>>=(size_type const n) {
    vmanip::rshift(data, n);

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

BigCub BigCub::operator*(BigCub const &n) const {
    BigCub toReturn(*this);
    toReturn *= n;
    
    return toReturn;
}

BigCub BigCub::operator-() const {
    BigCub toReturn(*this);
    vmanip::invert(toReturn.data);
    
    return toReturn;
}

BigCub &BigCub::operator++() {
    vmanip::add(data, {true, false}, data);
    
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

BigCub BigCub::operator<<(size_type const n) const {
    BigCub toReturn(*this);
    toReturn <<= n;
    
    return toReturn;
}

BigCub BigCub::operator>>(size_type const n) const {
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
