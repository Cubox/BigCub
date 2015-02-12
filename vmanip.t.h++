//
//  vmanip.t.h++
//  bigcub
//
//  Created by Andy Pilate on 29/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#ifndef vmanip_t_h
#define vmanip_t_h

#include <climits>

#include "vmanip.h++"

template<typename T, typename>
vmanip::Type vmanip::intImport(T const &n) {
    Type toReturn;
    
    if (std::is_unsigned<T>::value) { // Unsigned, see lower
        toReturn.resize((sizeof(n) * CHAR_BIT) + 1);
    }
    else {
        toReturn.resize(sizeof(n) * CHAR_BIT);
    }
    
    size_type i = 0;
    for (; i < sizeof(n) * CHAR_BIT; ++i) {
        toReturn[i] = (n >> i) & 1;
    }
    
    if (std::is_unsigned<T>::value) { // If unsigned, we need to convert into
        toReturn[i] = false;          // signed form.
    }
    
    return toReturn;
}

template<typename T, typename>
T vmanip::intExport(Type const &n) {
    T toReturn = 0;
    
    if (n.size() == 0) {
        return toReturn;
    }
    
    size_type i = 0;
    for (; (i < n.size()) && i < sizeof(T) * CHAR_BIT; ++i) {
        toReturn |= (static_cast<T>(n[i]) << i);
    }
    
    for (; n.back() == true && i < sizeof(T) * CHAR_BIT; ++i) {
        toReturn |= (static_cast<T>(n.back()) << i);
    }
    
    return toReturn;
}

template<class BinaryOperation>
void vmanip::transform(Type a, Type b, Type &dest, BinaryOperation op) {
    normalize(a, b);
    
    dest.resize(a.size());
    
    for (size_type i = 0; i < dest.size(); ++i) {
        dest[i] = op(a[i], b[i]);
    }
}

template<class UnaryOperation>
void vmanip::transform(Type &dest, UnaryOperation op) {
    for (auto i : dest) {
        dest[i] = op();
    }
}

#endif
