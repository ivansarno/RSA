//
//  Prime.cpp
//  RSA
//
//  Created by ivan sarno on 28/07/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.5

#include "Prime.h"

using namespace RSA;
using namespace RSA::Prime;

//component of Miller-Rabin primality test
inline void MRscomposition(const BigInteger &N, unsigned int &w, BigInteger &z)
{
    z = N - 1;
    w = 0;
    while(BigInteger(z&1) == 0)
    {
        w++;
        z >>= 1;
    }
}

inline bool MRpredicate1 (const BigInteger &y, const BigInteger &z, const BigInteger &N)
{
    return (Utils::mod_pow(y,z,N)==1);
}

bool MRpredicate2(const BigInteger &y, const BigInteger &N, const BigInteger &z, const unsigned int &w)
{
    unsigned int i = 0;
    BigInteger pow2 = 1;
    bool cond = BigInteger(Utils::mod_pow(y, z, N)) == BigInteger(N-1);
    
    while (!cond && i < w)
    {
        i++;
        pow2 <<= 1;
        cond = (Utils::mod_pow(y, pow2*z, N) == BigInteger(N-1));
    }
    
    return i != w;
}

bool MRtest(const BigInteger &N, TestGenerator *gen, unsigned int size, unsigned int precision)  //Miller-rabin test for prime number
{
    unsigned int w; BigInteger z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;//default result
    int i=0;
    
    
    BigInteger y;
    
    while (ris && i < precision)
    {
        y = gen->get(size) % N;
        
        while(y<2)//avoid random number < 2
        {
            y += gen->get(64);
        }
        ris = (coprime(y,N)) && (MRpredicate1(y, z, N)|| MRpredicate2(y, N, z, w));
        i++;
    }
    return ris;
}

//extract a random number and search a early prime
BigInteger Prime::NextPrime(BigInteger current, unsigned long long seed, unsigned int size, unsigned int precision)
{
    auto gen = TestGenerator(seed);
    if (BigInteger(current & 1)==0)
        current++;
    
    while (!MRtest(current, &gen, size, precision))
    {
        current +=2;
    }
    
    return current;
}

bool Prime::IsPrime(const BigInteger &number, unsigned long long seed, unsigned int size, unsigned int precision)
{
    auto gen = TestGenerator(seed);
    return (number==2) || ((number>2) && MRtest(number, &gen, size, precision));
}