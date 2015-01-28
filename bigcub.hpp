/*
 *  bigcub.h
 *  bigcub
 *
 *  Created by Andy Pilate on 19/01/15.
 *  Copyright (c) 2015 Andy Pilate. All rights reserved.
 *
 */

#ifndef bigcub_h
#define bigcub_h

#include <vector>
#include <string>
#include <ostream>
#include "vmanip.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

class BigCub {
public:
    using Type = vmanip::Type;
    
    template<typename T>
    using IntOnly = typename std::enable_if<std::is_integral<T>::value>::type;
    
	BigCub(void);
    BigCub(Type const &n);
    BigCub(char const* const str);
    BigCub(std::string const &str);
    
    template<typename T, typename = IntOnly<T>>
    explicit BigCub(T const &n);
    
    BigCub(BigCub const &n);
    BigCub &operator=(BigCub const &toAssign);
    
    ~BigCub();
    
    Type &getRawBits();
    
    BigCub operator+(BigCub const &n) const;
    
    template<typename T, typename = IntOnly<T>>
    BigCub operator+(T const &n) const;
    
    BigCub &operator+=(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    BigCub &operator+=(T const &n);
    
    BigCub operator-(BigCub const &n) const;
    
    template<typename T, typename = IntOnly<T>>
    BigCub operator-(T const &n) const;
    
    BigCub &operator-=(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    BigCub &operator-=(T const &n);
    
    BigCub operator-() const;
    
    BigCub &operator++();
    BigCub operator++(int);
    
    BigCub &operator--();
    BigCub operator--(int);
    
    BigCub operator~() const;
    
    bool operator==(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    bool operator==(T const &n);
    
    bool operator!=(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    bool operator!=(T const &n);
    
    bool operator<(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    bool operator<(T const &n);
    
    bool operator>(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    bool operator>(T const &n);
    
    bool operator<=(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    bool operator<=(T const &n);
    
    bool operator>=(BigCub const &n);
    
    template<typename T, typename = IntOnly<T>>
    bool operator>=(T const &n);
    
    template<typename T, typename = IntOnly<T>>
    operator T() const;
    
protected:
    Type data;
};

std::ostream &operator<<(std::ostream &o, BigCub const &n);

template<typename T, typename>
BigCub::BigCub(T const &n) {
    data = vmanip::intImport(n);
}

template<typename T, typename>
BigCub BigCub::operator+(T const &n) const {
    BigCub toReturn;
    vmanip::add(data, vmanip::intImport(n), toReturn.data);
    
    return toReturn;
}

template<typename T, typename>
BigCub &BigCub::operator+=(T const &n) {
    *this = *this + n;
    return *this;
}

template<typename T, typename>
BigCub BigCub::operator-(T const &n) const {
    BigCub toReturn;
    vmanip::add(data, vmanip::intImport(-n), toReturn.data);
    
    return toReturn;
}

template<typename T, typename>
BigCub &BigCub::operator-=(T const &n) {
    *this = *this - n;
    return *this;
}

template<typename T, typename>
BigCub::operator T() const {
    return vmanip::intExport<T>(data);
}

template<typename T, typename>
bool BigCub::operator==(T const &n) {
    return vmanip::compare(data, vmanip::intImport<T>(n)) == 0;
}

template<typename T, typename>
bool BigCub::operator!=(T const &n) {
    return vmanip::compare(data, vmanip::intImport<T>(n)) != 0;
}

template<typename T, typename>
bool BigCub::operator>(T const &n) {
    return vmanip::compare(data, vmanip::intImport<T>(n)) > 0;
}

template<typename T, typename>
bool BigCub::operator<(T const &n) {
    return vmanip::compare(data, vmanip::intImport<T>(n)) < 0;
}

template<typename T, typename>
bool BigCub::operator>=(T const &n) {
    return vmanip::compare(data, vmanip::intImport<T>(n)) >= 0;
}

template<typename T, typename>
bool BigCub::operator<=(T const &n) {
    return vmanip::compare(data, vmanip::intImport<T>(n)) <= 0;
}

#pragma GCC visibility pop
#endif
