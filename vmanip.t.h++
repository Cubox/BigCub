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

// Convert an integer into a Type of the same value

template<typename T, typename>
vmanip::Type vmanip::intImport(T const &n) {
    Type toReturn;
    
    toReturn.resize(sizeof(n) * CHAR_BIT);
    
    size_type i = 0;
    for (; i < sizeof(n) * CHAR_BIT; ++i) {
        toReturn[i] = (n >> i) & 1;
    }
    
    if (std::is_unsigned<T>::value) { // If unsigned, we need to convert into
        toReturn.push_back(false);    // signed form.
    }
    
    return toReturn;
}

// Convert a Type to an integer of the same value.
// The required integer is specified via the template parameter

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
    
    // if the number is negative, fill the remaining bits to one
    for (; n.back() == true && i < sizeof(T) * CHAR_BIT; ++i) {
        toReturn |= (static_cast<T>(n.back()) << i);
    }
    
    return toReturn;
}

// Apply the passed function to each bits in a and b

template<class BinaryOperation>
void vmanip::transform(Type a, Type b, Type &dest, BinaryOperation op) {
    normalize(a, b);
    
    dest.resize(a.size());
    
    for (size_type i = 0; i < dest.size(); ++i) {
        dest[i] = op(a[i], b[i]);
    }
}

// Apply the passed function to each bits in dest

template<class UnaryOperation>
void vmanip::transform(Type &dest, UnaryOperation op) {
    for (size_type i = 0; i < dest.size(); ++i) {
        dest[i] = op();
    }
}

#endif
