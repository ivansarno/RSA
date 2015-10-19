//
//  Prime.cpp
//  RSA
//
//  Created by ivan sarno on 28/07/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.2

#include "Prime.h"

using namespace RSA;
using namespace RSA::Prime;

//component of Miller-Rabin primality test
void MRscomposition(BigInteger N, BigInteger &w, BigInteger &z)
{
    BigInteger i=1;
    BigInteger acc=2;
    N--;
    BigInteger r;
    while (acc < N)
    {
        r=N/acc;
        if ((N%acc==0) && (r%2==1))
        {
            w=i;
            z=r;
        }
        i++;
        acc = acc * 2;
    }
}

bool MRpredicate1 (const BigInteger &y, const BigInteger &z, const BigInteger &N)
{
    if (Aux::mod_pow(y,z,N)==1)
        return true;
    else return false;
}

bool MRpredicate2(const BigInteger &y, const BigInteger &N, const BigInteger &z, const BigInteger &w)
{
    BigInteger i=0;
    bool cond = (Aux::mod_pow(y,Aux::pow(2,i)*z, N) == N-1);
    
    while (!cond && i < w)
    {
        i++;
        cond = (Aux::mod_pow(y,Aux::pow(2,i)*z, N) == N-1);
    }
    
    if (i==w)
        return false;
    else return true;
    
}

bool MRtest(const BigInteger &N, Generator &gen, unsigned int size, unsigned int precision)  //Miller-rabin test for prime number
{
    BigInteger w; BigInteger z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;//default result
    int i=0;
    
    
    BigInteger y;
    
    while (ris && i < precision)
    {
        y = gen.get(size);
        y= y % N;
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
BigInteger Prime::Generates(Aux::Generator &gen, unsigned int size, unsigned int precision)
{
    BigInteger P = gen.get(size);
    if (P%2==0)
        P++;
    
    while (!MRtest(P, gen, size, precision))
    {
        P = P+2;
    }
    
    return P;
}

bool Prime::IsPrime(const BigInteger &number, Aux::Generator &gen, unsigned int size, unsigned int precision)
{
    return MRtest(number, gen, size, precision);
}