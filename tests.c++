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
    for (uint32_t i = 0; i < INT_MAX; ++i ) {
        BigCub tmp1(i);
        BigCub tmp2(i);
        
        cassert(tmp1 + tmp2 == i + i);
        cassert(tmp1 + (tmp2 + 10) == i + (i + 10));
        cassert(++tmp1 == ++i);
        cassert(--tmp1 == --i);
        cassert(-tmp1 == -i);
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
    for (uintmax_t i = 0; i < ULLONG_MAX; ++i) {
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
        cassert((tmp2 < i) == (i < -i));
        cassert((tmp2 > i) == (i > -i));
        cassert((tmp2 <= i) == (i <= -i));
        cassert((tmp2 >= i) == (i >= -i));
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

int main() {
//    initTests();
//    arithTests();
    
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
//
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
