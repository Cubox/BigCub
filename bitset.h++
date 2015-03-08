//
//  bitset.h++
//  bigcub
//
//  Created by Andy Pilate on 03/03/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#ifndef bitset_h
#define bitset_h

#include <cstdint>
#include <deque>
#include <string>
#include <__bit_reference>

namespace vmanip {
    template<typename T = uint64_t>
    class Bitset {
    public:
        typedef size_t size_type;
        typedef Bitset __self;
        typedef std::__bit_reference<__self> reference;
        typedef const std::__bit_const_reference<__self> const_reference;
        typedef T __storage_type;
        typedef T* __storage_pointer;
        typedef const T* __const_storage_pointer;
        static const size_type bits_per_word = sizeof(T) * CHAR_BIT;
        
        inline Bitset();
        Bitset(Bitset const &bits);
        Bitset(Bitset &&bits);
        Bitset(std::initializer_list<bool> list);
        Bitset(size_type size);
        ~Bitset() = default;
        
        Bitset &operator=(Bitset const &bits);
        Bitset &operator=(Bitset &&bits);
        
        inline size_type size() const;
        inline void flip();
        
        inline void resize(size_type n);
        inline void clear();
        
        void push_front(bool bit);
        inline void push_front(std::initializer_list<bool> list);
        inline void push_front(size_type n, bool bit);
        void push_back(bool bit);
        inline void push_back(std::initializer_list<bool> list);
        inline void push_back(size_type n, bool bit);
        
        void pop_front();
        inline void pop_front(size_type n);
        void pop_back();
        inline void pop_back(size_type n);
        
        inline reference front();
        inline const_reference front() const;
        inline reference back();
        inline const_reference back() const;
        
        inline reference operator[](size_type n);
        inline const_reference operator[](size_type n) const;
        
        inline std::deque<T> *operator->();
        
        inline std::string to_string() const;
        
        size_type front_offset;
    protected:
        size_type _size;
        std::deque<T> bits;
        
    private:
        inline reference make_ref(size_type n);
        inline const_reference make_ref(size_type n) const;
    };
}


template<typename T>
struct std::__has_storage_type<vmanip::Bitset<T>>
{
    static const bool value = true;
};

#include "bitset.t.h++"

#endif
