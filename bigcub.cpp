#include <vector>
#include <string>
#include <locale>
#include <cmath>
#include <ostream>

#include "vmanip.hpp"
#include "bigcub.hpp"

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
    if (str == NULL || str[0] == '\0') {
        return;
    }
    
    bool negative = false;
    
    if (str[0] == '-') {
        negative = true;
    }
    
    size_t strSize = std::strlen(str);
    str = str + (strSize - 1);
    for (size_t i = 1; i <= strSize; ++i, --str) {
        if (std::isdigit(*str)) { // oh god this is horrible pls fix
            *this += (*str - '0') * static_cast<uintmax_t>(std::pow(10, i - 1));
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

// Public getters

BigCub::Type &BigCub::getRawBits() {
    return data;
}

// Assignation operators

BigCub &BigCub::operator=(BigCub const &n) {
    data = std::vector<bool>(n.data);
    vmanip::compress(data);
    
    return *this;
}

BigCub &BigCub::operator+=(BigCub const &n) {
    *this = *this + n;
    return *this;
}

BigCub &BigCub::operator-=(BigCub const &n) {
    *this = *this - n;
    return *this;
}

// Arithmetic operators

BigCub BigCub::operator+(BigCub const &n) const {
	BigCub toReturn;
    
    vmanip::add(data, n.data, toReturn.data);
    
    return toReturn;
}

BigCub BigCub::operator-(BigCub const &n) const {
    BigCub toReturn;
    
    Type invertedOther = n.data;
    vmanip::invert(invertedOther);
    vmanip::add(data, invertedOther, toReturn.data);
    
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
    BigCub toReturn;
    
    Type one = {true, false};
    vmanip::add(data, one, toReturn.data);
    
    return toReturn;
}

BigCub &BigCub::operator--() {
    Type one = {true, true};
    vmanip::add(data, one, data);
    
    return *this;
}

BigCub BigCub::operator--(int) {
    BigCub toReturn;
    
    Type one = {true, true};
    vmanip::add(data, one, toReturn.data);
    
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

