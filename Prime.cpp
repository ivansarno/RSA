//
//  Prime.cpp
//  RSA
//
//  Created by ivan sarno on 28/07/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.4

#include "Prime.h"

using namespace RSA;
using namespace RSA::Prime;

//component of Miller-Rabin primality test
void MRscomposition(BigInteger N, unsigned int &w, BigInteger &z)
{
    z = N - 1;
    w = 0;
    while((z&1) == 0)
    {
        w++;
        z >>= 1;
    }
}

bool MRpredicate1 (const BigInteger &y, const BigInteger &z, const BigInteger &N)
{
    return (Utils::mod_pow(y,z,N)==1);
}

bool MRpredicate2(const BigInteger &y, const BigInteger &N, const BigInteger &z, const unsigned int &w)
{
    unsigned int i = 0;
    BigInteger pow2 = 1;
    bool cond = (Utils::mod_pow(y, z, N) == N-1);
    
    while (!cond && i < w)
    {
        i++;
        pow2 <<= 1;
        cond = (Utils::mod_pow(y, pow2*z, N) == N-1);
    }
    
    return i != w;
}

bool MRtest(const BigInteger &N, Generator &gen, unsigned int size, unsigned int precision)  //Miller-rabin test for prime number
{
    unsigned int w; BigInteger z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;//default result
    int i=0;
    
    
    BigInteger y;
    
    while (ris && i < precision)
    {
        y = gen.get(size);
        y = y % N;
        while(y<2)//avoid random number < 2
        {
            y = gen.get(size);
            y= y % N;
        }
        ris = (coprime(y,N)) && (MRpredicate1(y, z, N)|| MRpredicate2(y, N, z, w));
        i++;
    }
    return ris;
}

//extract a random number and search a early prime
BigInteger Prime::Generates(Utils::Generator &gen, unsigned int size, unsigned int precision)
{
    BigInteger P = gen.get(size);
    if ((P & 1)==0)
        P++;
    
    while (!MRtest(P, gen, size, precision))
    {
        P = P+2;
    }
    
    return P;
}

bool Prime::IsPrime(const BigInteger &number, Utils::Generator &gen, unsigned int size, unsigned int precision)
{
    return MRtest(number, gen, size, precision);
}