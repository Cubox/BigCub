//
//  vmanip.hpp
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
    typedef Type::size_type size_type;
    
    template<typename T>
    using IntOnly = typename std::enable_if<std::is_integral<T>::value>::type;
    
    template<typename T, typename = IntOnly<T>>
    Type intImport(T const &n);
    
    template<typename T, typename = IntOnly<T>>
    T intExport(Type const &n);
    
    template<class BinaryOperation>
    void transform(Type a, Type b, Type &dest, BinaryOperation op);
    
    template<class UnaryOperation>
    void transform(Type &dest, UnaryOperation op);
    
    void add(Type a, Type b, Type &dest);
    void extend(Type &a, Type &b);
    void compress(Type &bits);
    void invert(Type &bits);
    int8_t compare(Type a, Type b);
}

#include "vmanip.t.h++"

#pragma GCC visibility pop
#endif
