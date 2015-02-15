# BigCub

This is a Bignum library, in C++.

Almost every arithmetic and logic operators are overloaded on the BigCub class. The only missing operation is the division.

Probably missing some logic operators. vOv

## How to build it?

You need Tup installed.
You need clang, with C++14 support.

```shell
$ $(package manager) install tup
$ tup init
$ tup
$ ./tests
```

## Why? How?

The reason behind this code was to have fun, learn how to do bignum operations and how it all worked. My choice of storing numbers in a vector<bool> is a bad idea for a serious lib, but it made me do a lot of paper binary operations!

Performances are not that bad, for a basic recurring fibonacci function, using BigCub will take only 3 times as libgmp does!
