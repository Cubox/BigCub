//
//  vmanip.h
//  bigcub
//
//  Created by Andy Pilate on 21/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#ifndef vmanip_h
#define vmanip_h

#include <vector>

#pragma GCC visibility push(default)

namespace vmanip {
    typedef std::vector<bool> Type;
    
    template<typename T>
    using IntOnly = typename std::enable_if<std::is_integral<T>::value>::type;
    
    template<typename T, typename = IntOnly<T>>
    Type intImport(T const &n);
    
    template<typename T, typename = IntOnly<T>>
    T intExport(Type const &n);
    
    void add(Type a, Type b, Type &dest);
    void extend(Type &a, Type &b);
    void compress(Type &bits);
    void invert(Type &bits);
    int8_t compare(Type a, Type b);
}

template<typename T, typename>
vmanip::Type vmanip::intImport(T const &n) {
    Type toReturn;
    toReturn.reserve(sizeof(n) * CHAR_BIT);
    
    for (size_t i = 0; i < sizeof(n) * CHAR_BIT; ++i) {
        toReturn.push_back((n >> i) & static_cast<T>(1));
    }
    
    if (std::is_unsigned<T>::value) { // If unsigned, we need to convert into
        toReturn.push_back(false);    // signed form.
    }
    
    compress(toReturn);
    return toReturn;
}

template<typename T, typename>
T vmanip::intExport(Type const &n) {
    T toReturn = 0;
    
    if (n.size() == 0) {
        return toReturn;
    }
    
    size_t i = 0;
    for (; (i < n.size()) && i < sizeof(T) * CHAR_BIT; ++i) {
        toReturn |= (static_cast<T>(n[i]) << i);
    }
    
    for (; n.back() == true && i < sizeof(T) * CHAR_BIT; ++i) {
        toReturn |= (static_cast<T>(n.back()) << i);
    }
    
    return toReturn;
}

#pragma GCC visibility pop
#endif /* defined(vmanip_h) */
