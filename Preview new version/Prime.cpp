//
//  Prime.cpp
//  RSA
//
//  Created by ivan sarno on 28/07/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#include "Prime.h"

using namespace Prime;

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

bool MRpredicate1 (BigInteger y, BigInteger z, BigInteger N, int size)
{
    if (Aux::mod_pow(y,z,N,size)==1)
        return true;
    else return false;
}

bool MRpredicate2(BigInteger y, BigInteger N, BigInteger z, BigInteger w, int size)
{
    BigInteger i=0;
    bool cond = (Aux::mod_pow(y,Aux::pow(2,i,size)*z, N, size) == N-1);
    
    while (!cond && i < w)
    {
        i++;
        cond = (Aux::mod_pow(y,Aux::pow(2,i,size)*z, N, size) == N-1);
    }
    
    if (i==w)
        return false;
    else return true;
    
}

bool MRtest(BigInteger N, Generator gen, int size, int precision)  //Miller-rabin test for prime number
{
    BigInteger w; BigInteger z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;
    int i=0;
    
    
    BigInteger y;
    
    while (ris && i < precision)
    {
        y = gen.get(size);
        y= y % N;
        while(y<2)
        {
            y = gen.get(size);
            y= y % N;
        }
        ris = (coprime(y,N)) && (MRpredicate1(y, z, N, size)|| MRpredicate2(y, N, z, w, size));
        i++;
    }
    return ris;
}

//extract a random number and search a early prime
BigInteger Prime::Generates(Aux::Generator gen, int size, int precision)
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

bool Prime::IsPrime(BigInteger number, Aux::Generator gen, int size, int precision)
{
    return MRtest(number, gen, size, precision);
}