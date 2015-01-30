//
//  vmanip.cpp
//  bigcub
//
//  Created by Andy Pilate on 21/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#include "vmanip.h++"

void vmanip::add(Type a, Type b, Type &dest) {
    dest.clear();
    
    if (a.size() == 0) {
        dest = b;
        return;
    }
    else if (b.size() == 0) {
        dest = a;
        return;
    }
    
    extend(a, b);
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
    
    compress(dest);
}

void vmanip::compress(Type &bits) {
//    if (bits.size() == 0) {
//        return;
//    }
//    
//    size_type i = bits.size() - 1;
//    for (; i > 2 && bits[i] == bits[i - 1]; --i);
//    
//    bits.resize(i + 1);
}

void vmanip::invert(Type &bits) {
    if (bits.size() == 0) {
        return;
    }
    
    bits.flip();
    Type one = {true, false};
    add(bits, one, bits);
}

int8_t vmanip::compare(Type a, Type b) {
    extend(a, b);
    
    if (a.back() == false && b.back() == true) {
        return 1;
    }
    else if (a.back() == true && b.back() == false) {
        return -1;
    }
    
    for (size_type i = 0; i < a.size() - 1; ++i) {
        if (a[i] == false && b[i] == true) {
            return -1;
        }
        else if (a[i] == true && b[i] == false) {
            return 1;
        }
    }
    
    return 0;
}

void vmanip::extend(Type &a, Type &b) {
    if (a.size() < b.size()) {
        a.insert(a.end(), b.size() - a.size(), static_cast<bool>(a.back()));
    }
    else if (b.size() < a.size()) {
        b.insert(b.end(), a.size() - b.size(), static_cast<bool>(b.back()));
    }
}