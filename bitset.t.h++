//
//  bitset.t.h++
//  bigcub
//
//  Created by Andy Pilate on 03/03/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#ifndef bitset_t_h
#define bitset_t_h

#include <__bit_reference>
#include <iostream>
#include <cassert>

using vmanip::Bitset;

template<typename T>
Bitset<T>::Bitset() : front_offset(0), _size(0) {
    
}

template<typename T>
Bitset<T>::Bitset(Bitset const &who) {
    *this = who;
}

template<typename T>
Bitset<T>::Bitset(Bitset &&who) {
    *this = who;
}

template<typename T>
Bitset<T>::Bitset(std::initializer_list<bool> list) : Bitset() {
    for (auto i : list) {
        push_back(i);
    }
}

template<typename T>
Bitset<T>::Bitset(size_type size) : Bitset() {
    resize(size);
}

template<typename T>
Bitset<T> &Bitset<T>::operator=(Bitset const &who) {
    front_offset = who.front_offset;
    _size = who._size;
    bits = who.bits;
    
    return *this;
}

template<typename T>
Bitset<T> &Bitset<T>::operator=(Bitset &&who) {
    front_offset = std::move(who.front_offset);
    _size = std::move(who._size);
    bits = std::move(who.bits);
    
    return *this;
}

template<typename T>
typename Bitset<T>::size_type Bitset<T>::size() const {
    return (_size);
}

template<typename T>
void Bitset<T>::flip() {
    for (size_type i = 0; i < _size; ++i) {
        operator[](i).flip();
    }
}

template<typename T>
void Bitset<T>::resize(size_type n) {
    bits.resize(((n + front_offset - 1) / bits_per_word) + 1);
    _size = n;
}

template<typename T>
void Bitset<T>::clear() {
    bits.clear();
    front_offset = 0;
    _size = 0;
}

template<typename T>
void Bitset<T>::push_front(bool bit) {
    assert(front_offset <= bits_per_word);
    
    if (size() == 0 || front_offset == 0) { // We need to reallocate
        bits.push_front(0);
        front_offset = bits_per_word;
    }
    
    --front_offset;
    bits.front() |= static_cast<T>(bit) << (front_offset);
    _size++;
}

template<typename T>
void Bitset<T>::push_front(std::initializer_list<bool> list) {
    for (auto i : list) {
        push_front(i);
    }
}

template<typename T>
void Bitset<T>::push_front(size_type n, bool bit) {
    for (; n > 0; --n) {
        push_front(bit);
    }
}

template<typename T>
void Bitset<T>::push_back(bool bit) {
    size_type n = (_size + front_offset) % bits_per_word;
    
    if (size() == 0 || n == 0) { // We need to reallocate
        bits.push_back(0);
    }
    
    bits.back() |= static_cast<T>(bit) << n;
    _size++;
}

template<typename T>
void Bitset<T>::push_back(std::initializer_list<bool> list) {
    for (auto i : list) {
        push_back(i);
    }
}

template<typename T>
void Bitset<T>::push_back(size_type n, bool bit) {
    for (; n > 0; --n) {
        push_back(bit);
    }
}

template<typename T>
void Bitset<T>::pop_front() {
    if (front_offset == bits_per_word - 1) {
        bits.pop_front();
        front_offset = 0;
        _size--;
        return;
    }
    
    _size--;
    front_offset++;
}

template<typename T>
void Bitset<T>::pop_front(size_type n) {
    for (; n > 0; --n) {
        pop_front();
    }
}

template<typename T>
void Bitset<T>::pop_back() {
    if (_size % bits_per_word == 1) { // We can remove this word
        bits.pop_back();
    }
    
    _size--;
}

template<typename T>
void Bitset<T>::pop_back(size_type n) {
    for (; n > 0; --n) {
        pop_back();
    }
}

template<typename T>
typename Bitset<T>::reference Bitset<T>::make_ref(size_type n) {
    n += front_offset;
    assert((n / bits_per_word) < bits.size());
    return reference(&bits[n / bits_per_word], static_cast<T>(T(1) << n % bits_per_word));
}

template<typename T>
typename Bitset<T>::const_reference Bitset<T>::make_ref(size_type n) const {
    n += front_offset;
    assert((n / bits_per_word) < bits.size());
    return const_reference(&bits[n / bits_per_word], static_cast<T>(T(1) << n % bits_per_word));
}

template<typename T>
typename Bitset<T>::reference Bitset<T>::front() {
    return make_ref(0);
}

template<typename T>
typename Bitset<T>::const_reference Bitset<T>::front() const {
    return make_ref(0);
}

template<typename T>
typename Bitset<T>::reference Bitset<T>::back() {
    return make_ref(size() - 1);
}

template<typename T>
typename Bitset<T>::const_reference Bitset<T>::back() const {
    return make_ref(size() - 1);
}

template<typename T>
typename Bitset<T>::reference Bitset<T>::operator[](size_type n) {
    return make_ref(n);
}

template<typename T>
typename Bitset<T>::const_reference Bitset<T>::operator[](size_type n) const {
    return make_ref(n);
}

template<typename T>
std::deque<T> *Bitset<T>::operator->() {
    return &bits;
}

template<typename T>
std::string Bitset<T>::to_string() const {
    std::string toReturn;
    toReturn.reserve(_size);
    
    for (size_type i = 0; i < _size; ++i) {
        toReturn += operator[](i) + '0';
    }
    
    return toReturn;
}

#endif
