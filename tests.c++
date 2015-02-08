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
    
//    std::cout << "Starting range arith tests" << std::endl;
//    
//    for (int32_t i = 0; i < INT_MAX; ++i ) {
//        BigCub tmp1(i);
//        BigCub tmp2(i);
//        
//        cassert(static_cast<int32_t>(tmp1 + tmp2) == static_cast<int32_t>(i + i));
//        cassert(static_cast<int32_t>(tmp1 + (tmp2 + 10)) == static_cast<int32_t>(i + (i + 10)));
//        cassert(static_cast<int32_t>(++tmp1) == static_cast<int32_t>(++i));
//        cassert(static_cast<int32_t>(--tmp1) == static_cast<int32_t>(--i));
//        cassert(static_cast<int32_t>(-tmp1) == static_cast<int32_t>(-i));
//        
//        cassert(static_cast<int32_t>(BigCub(i) * BigCub(i)) == static_cast<int32_t>(i * i));
//        
//        cassert(static_cast<int32_t>(BigCub(i) * BigCub(-i)) == static_cast<int32_t>(i * -i));
//    }
    
    std::random_device rd;
    
    std::cout << "Starting random arith tests" << std::endl;
    
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

        cassert(static_cast<int64_t>(BigCub(i1) * BigCub(i2)) == static_cast<int64_t>(i1 * i2));
    }
}

void cmpTests() {
//    std::cout << "Starting range cmp tests" << std::endl;
//    for (intmax_t i = 0; i < LLONG_MAX; ++i) {
//        BigCub tmp1(i);
//        BigCub tmp2(-i);
//        
//        cassert((tmp1 == tmp2) == (i == -i));
//        cassert((tmp1 != tmp2) == (i != -i));
//        cassert((tmp1 < tmp2) == (i < -i));
//        cassert((tmp1 > tmp2) == (i > -i));
//        cassert((tmp1 <= tmp2) == (i <= -i));
//        cassert((tmp1 >= tmp2) == (i >= -i));
//        
//        cassert((tmp2 == i) == (i == -i));
//        cassert((tmp2 != i) == (i != -i));
//        cassert((tmp2 < i) == (-i < i));
//        cassert((tmp2 > i) == (-i > i));
//        cassert((tmp2 <= i) == (-i <= i));
//        cassert((tmp2 >= i) == (-i >= i));
//    }
    
    std::cout << "Starting random cmp tests" << std::endl;
    
    std::random_device rd;
    
    for (auto i = 0; i < 100000; i++) {
        intmax_t i1 = rd();
        intmax_t i2 = -rd();
        
        BigCub tmp1(i1);
        BigCub tmp2(i2);
        
        cassert((BigCub(1) == BigCub(2)) == (1 == 2));
        cassert((BigCub(454545454545454) == BigCub(454545454545454)) == (454545454545454 == 454545454545454));
        
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
    
    std::cout << "Starting range bitwise tests" << std::endl;
    
//    for (intmax_t i = 0; i < LLONG_MAX; ++i) {
//        it = rd();
//        
//        cassert((BigCub(i) & BigCub(it)) == (i & it));
//        cassert((BigCub(i) | BigCub(it)) == (i | it));
//        cassert((BigCub(i) ^ BigCub(it)) == (i ^ it));
//        
//        //cassert(BigCub(it) << (static_cast<uintmax_t>(i) % 50) == static_cast<int32_t>(it) << (i % 50));
//        //cassert(BigCub(it) >> (static_cast<uintmax_t>(i) % 50) == static_cast<int32_t>(it) >> (i % 50));
//        
//        cassert(~BigCub(i) == ~i); // Can only use this if i is signed
//    }
    
    std::cout << "Starting random bitwise tests" << std::endl;
    
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

#define printBits(x) std::cout << "Printing " << #x << ": "; printBits2(x);
template<typename T>
void printBits2(T n) {
    for (size_t i = 0; i < sizeof(T) * CHAR_BIT; ++i) {
        std::cout << ((n >> i) & 1);
    }
    
    std::cout << std::endl;
}

int main() {
    //initTests();
    //arithTests();
    //cmpTests();
    //bitwiseTests();
    
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    BigCub a;
    
    //(*a).resize(INT_MAX+54554554);
    //a[a.size() - 1] = false;

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "BigCub took " << time_span.count() << " seconds." << std::endl;
    
    std::cout << "Value: " << a << std::endl;
    
//    for (auto i = (*a).begin(), e = (*a).end(); i != e; ++i) {
//        std::cout << *i;
//    }
    
    //td::cout << std::endl;
    
    std::chrono::high_resolution_clock::time_point t5 = std::chrono::high_resolution_clock::now();

//    mpz_class a3;
//    for (;mpz_sizeinbase(a3.get_mpz_t(), 2) < 25;) {
//        a3 += 1;
//    }
    

    std::chrono::high_resolution_clock::time_point t6 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span3 = std::chrono::duration_cast<std::chrono::duration<double>>(t6 - t5);

    std::cout << "libgmp took " << time_span3.count() << " seconds." << std::endl;

    
//    BigCub sum(0);
//    
//    for (size_t i = 0; i < 5000010; ++i) {
//        sum += ULLONG_MAX;
//    }
//    
//    std::cout << sum.size() << std::endl;
    
//    int a = 1;
//    printBits(a);
//    printBits(a >> 1);
//    printBits((BigCub(a) >> 1));
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
