//
//  bigcub.t++.h
//  bigcub
//
//  Created by Andy Pilate on 29/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#ifndef bigcub_t_h
#define bigcub_t_h

#include "bigcub.h++"

// Templated constructor

template<typename T, typename>
BigCub::BigCub(T const &n) {
    *this = n;
}

// Templated assignation operators

template<typename T, typename>
BigCub &BigCub::operator=(T const &n) {
    data = vmanip::intImport(n);
    
    return *this;
}

template<typename T, typename>
BigCub &BigCub::operator+=(T const &n) {
    vmanip::add(data, vmanip::intImport(n), data);
    
    return *this;
}

template<typename T, typename>
BigCub &BigCub::operator-=(T const &n) {
    vmanip::add(data, vmanip::intImport(-n), data);
    
    return *this;
}

template<typename T, typename>
BigCub &BigCub::operator&=(T const &n) {
    vmanip::transform(data, vmanip::intImport<T>(n), data, std::bit_and<bool>());
    
    return *this;
}

template<typename T, typename>
BigCub &BigCub::operator|=(T const &n) {
    vmanip::transform(data, vmanip::intImport<T>(n), data, std::bit_or<bool>());
    
    return *this;
}

template<typename T, typename>
BigCub &BigCub::operator^=(T const &n) {
    vmanip::transform(data, vmanip::intImport<T>(n), data, std::bit_xor<bool>());
    
    return *this;
}

// Templated arithmetic operators

template<typename T, typename>
BigCub BigCub::operator+(T const &n) const {
    BigCub toReturn(*this);
    toReturn += n;
    
    return toReturn;
}

template<typename T, typename>
BigCub BigCub::operator-(T const &n) const {
    BigCub toReturn(*this);
    toReturn -= n;
    
    return toReturn;
}

// Templated comparaison operators

template<typename T, typename>
bool BigCub::operator==(T const &n) const {
    return vmanip::compare(data, vmanip::intImport<T>(n)) == 0;
}

template<typename T, typename>
bool BigCub::operator!=(T const &n) const {
    return vmanip::compare(data, vmanip::intImport<T>(n)) != 0;
}

template<typename T, typename>
bool BigCub::operator<(T const &n) const {
    return vmanip::compare(data, vmanip::intImport<T>(n)) < 0;
}

template<typename T, typename>
bool BigCub::operator>(T const &n) const {
    return vmanip::compare(data, vmanip::intImport<T>(n)) > 0;
}

template<typename T, typename>
bool BigCub::operator<=(T const &n) const {
    return vmanip::compare(data, vmanip::intImport<T>(n)) <= 0;
}

template<typename T, typename>
bool BigCub::operator>=(T const &n) const {
    return vmanip::compare(data, vmanip::intImport<T>(n)) >= 0;
}

// Templated bitwise operators

template<typename T, typename>
BigCub BigCub::operator&(T const &n) const {
    BigCub toReturn(*this);
    toReturn &= n;
    
    return toReturn;
}

template<typename T, typename>
BigCub BigCub::operator|(T const &n) const {
    BigCub toReturn(*this);
    toReturn |= n;
    
    return toReturn;
}

template<typename T, typename>
BigCub BigCub::operator^(T const &n) const {
    BigCub toReturn(*this);
    toReturn ^= n;
    
    return toReturn;
}

// Templated cast operator

template<typename T, typename>
BigCub::operator T() const {
    return vmanip::intExport<T>(data);
}

#endif
