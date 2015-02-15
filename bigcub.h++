//
//  bigcub.hpp
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
#include "vmanip.h++"

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
    
#if 0
    
    BigCub(char const* const str);
    BigCub(std::string const &str);
    
#endif // 0
    
    template<typename T, typename = IntOnly<T>>
    BigCub(T const &n);
    
    // Destructor
    
    ~BigCub();
    
    // Internal data access related operators and functions
    
    Type::reference operator[](size_type n);
    Type::const_reference operator[](size_type n) const;
    Type::reference at(size_type n);
    Type::const_reference at(size_type n) const;
    Type &operator*();
    Type const &operator*() const;
    size_type size() const;
    void compress();
    
    // Assignation operators
    
    BigCub &operator=(BigCub const &n);
    BigCub &operator+=(BigCub const &n);
    BigCub &operator-=(BigCub const &n);
    BigCub &operator*=(BigCub const &n);
    BigCub &operator&=(BigCub const &n);
    BigCub &operator|=(BigCub const &n);
    BigCub &operator^=(BigCub const &n);
    BigCub &operator<<=(size_type const n);
    BigCub &operator>>=(size_type const n);
    
    // Arithmetic operators
    
    BigCub operator+(BigCub const &n) const;
    BigCub operator-(BigCub const &n) const;
    BigCub operator*(BigCub const &n) const;
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
    BigCub operator<<(size_type const n) const;
    BigCub operator>>(size_type const n) const;
    BigCub operator~() const;
    
    // Templated assignation operators
    
    template<typename T, typename = IntOnly<T>> BigCub &operator=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator+=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator-=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator*=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator&=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator|=(T const &n);
    template<typename T, typename = IntOnly<T>> BigCub &operator^=(T const &n);
    
    // Templated arithmetic operators
    
    template<typename T, typename = IntOnly<T>> BigCub operator+(T const &n) const;
    template<typename T, typename = IntOnly<T>> BigCub operator-(T const &n) const;
    template<typename T, typename = IntOnly<T>> BigCub operator*(T const &n) const;
    
    
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
    
    template<typename T, typename = IntOnly<T>> explicit operator T() const;
    
protected:
    Type data;
};

// std::cout overload

std::ostream &operator<<(std::ostream &o, BigCub const &n);

#include "bigcub.t.h++" // Template functions implementation

#pragma GCC visibility pop
#endif
