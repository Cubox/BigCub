//
//  main.cpp
//  tests
//
//  Created by Andy Pilate on 22/01/15.
//  Copyright (c) 2015 Andy Pilate. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <random>
#include <cstdint>
#include <chrono>
//#include <gmpxx.h>
#include <bigcub.h++>

#define cassert(x) assert(x)


void initTests() {
    BigCub tmp;
    cassert(static_cast<int>(tmp) == 0);

    for (uintmax_t i = 0; i < ULLONG_MAX; ++i) {
        BigCub tmp1(i);
        BigCub tmp2(-i);
        
        cassert(static_cast<uintmax_t>(tmp1) == i);
        cassert(static_cast<uintmax_t>(tmp2) == -i);
    }
}

void arithTests() {
    for (int32_t i = 0; i < INT_MAX; ++i ) {
        BigCub tmp1(i);
        BigCub tmp2(i);
        
        cassert(static_cast<int32_t>(tmp1 + tmp2) == static_cast<int32_t>(i + i));
        cassert(static_cast<int32_t>(tmp1 + (tmp2 + 10)) == static_cast<int32_t>(i + (i + 10)));
        cassert(static_cast<int32_t>(++tmp1) == static_cast<int32_t>(++i));
        cassert(static_cast<int32_t>(--tmp1) == static_cast<int32_t>(--i));
        cassert(static_cast<int32_t>(-tmp1) == static_cast<int32_t>(-i));
    }
    
    std::random_device rd;
    
    for (auto i = 0; i < 100000; i++) {
        intmax_t i1 = rd();
        intmax_t i2 = -rd();
        
        cassert(static_cast<int64_t>(BigCub(i1) + BigCub(i2)) == static_cast<int64_t>(i1 + i2));
        cassert(static_cast<int64_t>(BigCub(i1) - BigCub(i2)) == static_cast<int64_t>(i1 - i2));
        cassert(static_cast<int64_t>(-BigCub(i1) + BigCub(i2)) == static_cast<int64_t>(-i1 + i2));
        cassert(static_cast<int64_t>(BigCub(i1) + -BigCub(i2)) == static_cast<int64_t>(i1 + -i2));
        
        cassert(static_cast<int64_t>(BigCub(-i1) + BigCub(i2)) == static_cast<int64_t>(-i1 + i2));
        cassert(static_cast<int64_t>(BigCub(-i1) - BigCub(i2)) == static_cast<int64_t>(-i1 - i2));
        cassert(static_cast<int64_t>(-BigCub(-i1) + BigCub(i2)) == static_cast<int64_t>(i1 + i2));
        cassert(static_cast<int64_t>(BigCub(-i1) + -BigCub(i2)) == static_cast<int64_t>(-i1 + -i2));
        
        cassert(static_cast<int64_t>(BigCub(i1) + BigCub(-i2)) == static_cast<int64_t>(i1 + -i2));
        cassert(static_cast<int64_t>(BigCub(i1) - BigCub(-i2)) == static_cast<int64_t>(i1 - -i2));
        cassert(static_cast<int64_t>(-BigCub(i1) + BigCub(-i2)) == static_cast<int64_t>(-i1 + -i2));
        cassert(static_cast<int64_t>(BigCub(i1) + -BigCub(-i2)) == static_cast<int64_t>(i1 + i2));
        
        cassert(static_cast<int64_t>(BigCub(-i1) + BigCub(-i2)) == static_cast<int64_t>(-i1 + -i2));
        cassert(static_cast<int64_t>(BigCub(-i1) - BigCub(-i2)) == static_cast<int64_t>(-i1 - -i2));
        cassert(static_cast<int64_t>(-BigCub(-i1) + BigCub(-i2)) == static_cast<int64_t>(i1 + -i2));
        cassert(static_cast<int64_t>(BigCub(-i1) + -BigCub(-i2)) == static_cast<int64_t>(-i1 + i2));
        
        cassert(static_cast<int64_t>(++BigCub(i1)) == ++i1);
        cassert(static_cast<int64_t>(--BigCub(i1)) == --i1);
        
        cassert(static_cast<int64_t>(++BigCub(i2)) == ++i2);
        cassert(static_cast<int64_t>(--BigCub(i2)) == --i2);

        
    }
}

void cmpTests() {
    for (intmax_t i = 0; i < LLONG_MAX; ++i) {
        BigCub tmp1(i);
        BigCub tmp2(-i);
        
        cassert((tmp1 == tmp2) == (i == -i));
        cassert((tmp1 != tmp2) == (i != -i));
        cassert((tmp1 < tmp2) == (i < -i));
        cassert((tmp1 > tmp2) == (i > -i));
        cassert((tmp1 <= tmp2) == (i <= -i));
        cassert((tmp1 >= tmp2) == (i >= -i));
        
        cassert((tmp2 == i) == (i == -i));
        cassert((tmp2 != i) == (i != -i));
        cassert((tmp2 < i) == (-i < i));
        cassert((tmp2 > i) == (-i > i));
        cassert((tmp2 <= i) == (-i <= i));
        cassert((tmp2 >= i) == (-i >= i));
    }
    
    std::random_device rd;
    
    for (auto i = 0; i < 100000; i++) {
        intmax_t i1 = rd();
        intmax_t i2 = -rd();
        
        BigCub tmp1(i1);
        BigCub tmp2(i2);
        
        cassert((tmp1 == tmp2) == (i1 == i2));
        cassert((tmp1 != tmp2) == (i1 != i2));
        cassert((tmp1 < tmp2) == (i1 < i2));
        cassert((tmp1 > tmp2) == (i1 > i2));
        cassert((tmp1 <= tmp2) == (i1 <= i2));
        cassert((tmp1 >= tmp2) == (i1 >= i2));
        
    }
}

void bitwiseTests() {
    std::random_device rd;
    intmax_t it;
    
    for (intmax_t i = 0; i < LLONG_MAX; ++i) {
        it = rd();
        
        cassert((BigCub(i) & BigCub(it)) == (i & it));
        cassert((BigCub(i) | BigCub(it)) == (i | it));
        cassert((BigCub(i) ^ BigCub(it)) == (i ^ it));
        
        //cassert(BigCub(it) << (static_cast<uintmax_t>(i) % 50) == static_cast<int32_t>(it) << (i % 50));
        //cassert(BigCub(it) >> (static_cast<uintmax_t>(i) % 50) == static_cast<int32_t>(it) >> (i % 50));
        
        cassert(~BigCub(i) == ~i); // Can only use this if i is signed
    }
    
    intmax_t it2;
    
    for (uintmax_t i = 0; i < 100000; i++) {
        it = rd();
        it2 = -rd();
        
        cassert(BigCub(it2) & BigCub(it) == it2 & it);
        cassert(BigCub(it2) | BigCub(it) == it2 | it);
        cassert(BigCub(it2) ^ BigCub(it) == it2 ^ it);
        
        //cassert(BigCub(it) << i % 50 == it << i % 50);
        //cassert(BigCub(it) >> i % 50 == it >> i % 50);
        
        cassert(~BigCub(it) == ~it);
    }
}

//#define printBits(x) std::cout << "Printing " << #x << ": "; printBits2(x);
//template<typename T>
//void printBits2(T n) {
//    for (size_t i = 0; i < sizeof(T) * CHAR_BIT; ++i) {
//        std::cout << ((n >> i) & 1);
//    }
//    
//    std::cout << std::endl;
//}

int main() {
    //initTests();
    //arithTests();
    //cmpTests();
    //bitwiseTests();
    
    BigCub sum(0);
    
    for (size_t i = 0; i < 50000100; ++i) {
        sum += ULLONG_MAX;
    }
    
    std::cout << sum.size() << std::endl;
    
//    printBits(54565544 << 0);
//    printBits(54565544 << 1);
//    printBits(54565544 << 2);
//    printBits(54565544 << 3);
//    printBits(54565544 << 4);
//    printBits(54565544 << 5);
//    printBits(54565544 << 6);
//    printBits(54565544 << 7);
//    printBits(54565544 << 8);
//    printBits(54565544 << 9);
//    printBits(54565544 << 10);
//    printBits(54565544 << 11);
//    printBits(54565544 << 12);
//    printBits(54565544 << 13);
//    printBits(54565544 << 14);
//    printBits(54565544 << 15);
//    printBits(54565544 << 16);
//    printBits(54565544 << 17);
//    printBits(54565544 << 18);
//    printBits(54565544 << 19);
//    printBits(54565544 << 20);
//    printBits(54565544 << 21);
//    printBits(54565544 << 22);
//    printBits(54565544 << 23);
//    printBits(54565544 << 24);
//    printBits(54565544 << 25);
//    printBits(54565544 << 26);
//    printBits(54565544 << 27);
//    printBits(54565544 << 28);
//    printBits(54565544 << 29);
//    printBits(54565544 << 30);
//    printBits(54565544 << 31);
//    printBits(54565544 << 32);
//    printBits(54565544 << 33);
//    printBits(54565544 << -1);
    

    
    return 0;
}

//unsigned int ifib (unsigned int n){
//    if (n < 2)
//        return n;
//    else
//        return ifib(n - 1) + ifib(n - 2);
//}
//
//BigCub bfib(unsigned int n) {
//    if (n < 2) {
//        return BigCub(n);
//    } else {
//        return bfib(n - 1) + bfib(n - 2);
//    }
//}
//
//mpz_class gmpfib(unsigned int n) {
//    if (n < 2) {
//        return mpz_class(n);
//    } else {
//        return gmpfib(n - 1) + gmpfib(n - 2);
//    }
//}

//int main(int argc, char **argv) {
//    int howmuch = std::atoi(argv[1]);
//    
//    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//    
//    BigCub a1(bfib(howmuch));
//    
//    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
//    
//    std::cout << "BigCub fib took " << time_span.count() << " seconds." << std::endl;
//    
//    
//    
//    
//    std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
//    
//    unsigned int a2 = ifib(howmuch);
//    (void)a2;
//    
//    std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> time_span2 = std::chrono::duration_cast<std::chrono::duration<double>>(t4 - t3);
//    
//    std::cout << "int fib took " << time_span2.count() << " seconds." << std::endl;
//    
//    std::chrono::high_resolution_clock::time_point t5 = std::chrono::high_resolution_clock::now();
//    
//    mpz_class a3 = gmpfib(howmuch);
//    (void)a3;
//    
//    std::chrono::high_resolution_clock::time_point t6 = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> time_span3 = std::chrono::duration_cast<std::chrono::duration<double>>(t6 - t5);
//    
//    std::cout << "libgmp fib took " << time_span3.count() << " seconds." << std::endl;
//}
//
//int main2()
//{
//    int64_t i1 = 0;
//    int64_t i2 = 0;
//    size_t ok = 0;
//    size_t tried = 0;
//    
//    std::random_device rd;
//
//    for (size_t i = 0; i < 100000; ++i) {
//        i1 = rd();
//        i2 = -rd();
//        
//        cassert(static_cast<int64_t>(BigCub(i1) + BigCub(i2)) == static_cast<int64_t>(i1 + i2));
//        cassert(static_cast<int64_t>(BigCub(i1) - BigCub(i2)) == static_cast<int64_t>(i1 - i2));
//        cassert(static_cast<int64_t>(-BigCub(i1) + BigCub(i2)) == static_cast<int64_t>(-i1 + i2));
//        cassert(static_cast<int64_t>(BigCub(i1) + -BigCub(i2)) == static_cast<int64_t>(i1 + -i2));
//        
//        cassert(static_cast<int64_t>(BigCub(-i1) + BigCub(i2)) == static_cast<int64_t>(-i1 + i2));
//        cassert(static_cast<int64_t>(BigCub(-i1) - BigCub(i2)) == static_cast<int64_t>(-i1 - i2));
//        cassert(static_cast<int64_t>(-BigCub(-i1) + BigCub(i2)) == static_cast<int64_t>(i1 + i2));
//        cassert(static_cast<int64_t>(BigCub(-i1) + -BigCub(i2)) == static_cast<int64_t>(-i1 + -i2));
//        
//        cassert(static_cast<int64_t>(BigCub(i1) + BigCub(-i2)) == static_cast<int64_t>(i1 + -i2));
//        cassert(static_cast<int64_t>(BigCub(i1) - BigCub(-i2)) == static_cast<int64_t>(i1 - -i2));
//        cassert(static_cast<int64_t>(-BigCub(i1) + BigCub(-i2)) == static_cast<int64_t>(-i1 + -i2));
//        cassert(static_cast<int64_t>(BigCub(i1) + -BigCub(-i2)) == static_cast<int64_t>(i1 + i2));
//        
//        cassert(static_cast<int64_t>(BigCub(-i1) + BigCub(-i2)) == static_cast<int64_t>(-i1 + -i2));
//        cassert(static_cast<int64_t>(BigCub(-i1) - BigCub(-i2)) == static_cast<int64_t>(-i1 - -i2));
//        cassert(static_cast<int64_t>(-BigCub(-i1) + BigCub(-i2)) == static_cast<int64_t>(i1 + -i2));
//        cassert(static_cast<int64_t>(BigCub(-i1) + -BigCub(-i2)) == static_cast<int64_t>(-i1 + i2));
//        
//        cassert(static_cast<int64_t>(++BigCub(i1)) == ++i1);
//        cassert(static_cast<int64_t>(--BigCub(i1)) == --i1);
//        
//        cassert(static_cast<int64_t>(++BigCub(i2)) == ++i2);
//        cassert(static_cast<int64_t>(--BigCub(i2)) == --i2);
//        
//        ++i1;
//        --i2;
//        
//    }
//    
//    std::cout << "Success: " << ok << "/" << tried << " " << static_cast<double>((ok / static_cast<double>(tried)) * 100) << "%" << std::endl;
//
//    return 0;
//}
