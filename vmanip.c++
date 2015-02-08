//
//  vmanip.cpp
//  bigcub
//
//  Created by Andy Pilate on 21/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#include <cassert>
#include "vmanip.h++"

void vmanip::add(Type a, Type b, Type &dest /*, bool changeSize /* = true */) {
    dest.clear();
    
    if (a.size() == 0) {
        dest = b;
        return;
    }
    else if (b.size() == 0) {
        dest = a;
        return;
    }
    
    normalize(a, b /*, changeSize */);
    dest.resize(a.size());
    
    size_type i = 0;
    for (bool carry = false; i < dest.size(); ++i) {
        dest[i] = (a[i] ^ b[i] ^ carry);
        carry = (a[i] & b[i]) | (carry & (a[i] ^ b[i]));
    }
    --i;
    
    if (~(a[i] ^ b[i]) & (a[i] ^ dest[i])) {
        dest.push_back(a[i]);
    }
}

void vmanip::compress(Type &bits, size_type minSize) {
    if (bits.size() < 2 || bits.size() <= minSize) {
        return;
    }
    
    if (minSize < 2) {
        minSize = 2;
    }
    
    size_type i = bits.size() - 1;
    for (; i >= minSize && bits[i] == bits[i - 1]; --i);
    
    bits.resize(i + 1);
}

void vmanip::compress(Type &a, Type &b) {
    assert(a.size() == b.size());
    
    size_type size = a.size();
    if (size < 2) {
        return;
    }
    
    size_type i = size - 1;
    for (; i >= 2 && a[i] == a[i - 1] && b[i] == b[i - 1]; --i);
    
    a.resize(i + 1);
    b.resize(i + 1);
}

void vmanip::invert(Type &bits /*, bool changeSize /* = true */) {
    if (bits.size() == 0) {
        return;
    }
    
    bits.flip();
    Type one = {true, false};
    add(bits, one, bits /*, changeSize */);
}

int8_t vmanip::compare(Type a, Type b) {
    normalize(a, b);
    
    if (a.back() == false && b.back() == true) {
        return 1;
    }
    else if (a.back() == true && b.back() == false) {
        return -1;
    }
    
    size_type size = a.size() - 1;
    for (size_type i = 1; i <= size; ++i) {
        if (a[size - i] == false && b[size - i] == true) {
            return -1;
        }
        else if (a[size - i] == true && b[size - i] == false) {
            return 1;
        }
    }
    
    return 0;
}

void vmanip::normalize(Type &a, Type &b /*, bool changeSize /* = true */) {
    if (a.size() < b.size()) {
        // if (changeSize) {
        compress(b, a.size());
        // }
        
        if (a.size() == 0) {
            a.insert(a.end(), b.size() - a.size(), false);
        }
        else {
            a.insert(a.end(), b.size() - a.size(), static_cast<bool>(a.back()));
        }
    }
    else if (b.size() < a.size()) {
        // if (changeSize) {
        compress(a, b.size());
        // }
        
        if (b.size() == 0) {
            b.insert(b.end(), a.size() - b.size(), false);
        }
        else {
            b.insert(b.end(), a.size() - b.size(), static_cast<bool>(b.back()));
        }
    }
    else {
        // if (changeSize) {
        compress(a, b);
        // }
    }
}

void vmanip::lshift(Type &bits, size_type n) {
    if (n >= bits.size()) {
        transform(bits, [](){return false;});
    }
    else {
        bits.erase(bits.end() - static_cast<Type::difference_type>(n), bits.end());
        bits.insert(bits.begin(), n, false);
    }
}

void vmanip::rshift(Type &bits, size_type n) {
    if (n >= bits.size()) {
        vmanip::transform(bits, [&bits](){return bits.back();});
    }
    else {
        bits.erase(bits.begin(), bits.begin() + static_cast<Type::difference_type>(n));
        bits.insert(bits.end() - static_cast<Type::difference_type>(n), n, static_cast<bool>(bits.back()));
    }
}

void vmanip::mul(Type m, Type r, Type &P) {
    normalize(m, r);
    size_type size = m.size();
    
    P = r;
    Type A(m);
    invert(m /*, true */);
    Type S(m);
    
    A.insert(A.begin(), size + 1, false);
    S.insert(S.begin(), size + 1, false);
    P.insert(P.begin(), false);
    P.insert(P.end(), size, false);
    
    for (size_type i = 0; i < size; ++i) {
        if (P[0] == true && P[1] == false) {
            add(P, A, P);
        }
        else if (P[0] == false && P[1] == true) {
            add(P, S, P);
        }
        
        rshift(P, 1);
    }
    
    P.erase(P.end());
    P.erase(P.begin());
}
