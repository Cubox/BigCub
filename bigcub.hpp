//
//  bigcub.h
//  bigcub
//
//  Created by Andy Pilate on 19/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//
//

#ifndef bigcub_h
#define bigcub_h

#include <vector>
#include <string>
#include <ostream>
#include "vmanip.hpp"

// The classes below are exported
#pragma GCC visibility push(default)

class BigCub {
public:
    using Type = vmanip::Type;
    using size_type = Type::size_type;
    
    template<typename T>
    using IntOnly = typename std::enable_if<std::is_integral<T>::value>::type;
    
    // Constructors
    
    BigCub(void);
    BigCub(BigCub const &n);
    BigCub(Type const &n);
    BigCub(char const* const str);
    BigCub(std::string const &str);
    template<typename T, typename = IntOnly<T>>
    BigCub(T const &n);
    
    // Destructor
    
    ~BigCub();
    
    // Internal data access related operators
    
    Type::reference operator[](size_type n);
    Type::const_reference const operator[](size_type n) const;
    Type::reference at(size_type n);
    Type::const_reference const at(size_type n) const;
    Type &operator*();
    Type const &operator*() const;
    size_type size() const;
    
    // Assignation operators
    
    BigCub &operator=(BigCub const &n);
    BigCub &operator+=(BigCub const &n);
    BigCub &operator-=(BigCub const &n);
    BigCub &operator&=(BigCub const &n);
    BigCub &operator|=(BigCub const &n);
    BigCub &operator^=(BigCub const &n);
    BigCub &operator<<=(size_type const &n);
    BigCub &operator>>=(size_type const &n);
    
    // Arithmetic operators
    
    BigCub operator+(BigCub const &n) const;
    BigCub operator-(BigCub const &n) const;
    BigCub operator-() const;
    BigCub &operator++();
    BigCub operator++(int);
    BigCub &operator--();
    BigCub operator--(int);
    
    // Comparaison operators
    
    bool operator==(BigCub const &n) const;
    bool operator!=(BigCub const &n) const;
    bool operator<(BigCub const &n) const;
    bool operator>(BigCub const &n) const;
    bool operator<=(BigCub const &n) const;
    bool operator>=(BigCub const &n) const;

    // Bitwise operators
    
    BigCub operator&(BigCub const &n) const;
    BigCub operator|(BigCub const &n) const;
    BigCub operator^(BigCub const &n) const;
    BigCub operator<<(size_type const &n) const;
    BigCub operator>>(size_type const &n) const;
    BigCub operator~() const;
    
    // Templated assignation operators
    
    template<typename T, typename = IntOnly<T>> BigCub &operator=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator+=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator-=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator&=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator|=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator^=(T const &n);
    
    // Templated arithmetic operators
    
    template<typename T, typename = IntOnly<T>> BigCub operator+(T const &n) const;
    template<typename T, typename = IntOnly<T>> BigCub operator-(T const &n) const;
    
    
    // Templated comparaison operators
    
    template<typename T, typename = IntOnly<T>> bool operator==(T const &n) const;
    template<typename T, typename = IntOnly<T>> bool operator!=(T const &n) const;
    template<typename T, typename = IntOnly<T>> bool operator<(T const &n) const;
    template<typename T, typename = IntOnly<T>> bool operator>(T const &n) const;
    template<typename T, typename = IntOnly<T>> bool operator<=(T const &n) const;
    template<typename T, typename = IntOnly<T>> bool operator>=(T const &n) const;
    
    // Templated bitwise operators
    
    template<typename T, typename = IntOnly<T>> BigCub operator&(T const &n) const;
    template<typename T, typename = IntOnly<T>> BigCub operator|(T const &n) const;
    template<typename T, typename = IntOnly<T>> BigCub operator^(T const &n) const;
    
    // Templated cast operator
    
    template<typename T, typename = IntOnly<T>> operator T() const;
    
protected:
    Type data;
};

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

// std::cout overload

std::ostream &operator<<(std::ostream &o, BigCub const &n);

#pragma GCC visibility pop
#endif
