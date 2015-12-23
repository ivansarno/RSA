//
//  Prime.h
//  RSA
//
//  Created by ivan sarno on 28/07/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.5

#ifndef __RSA__Prime__
#define __RSA__Prime__
#include <gmpxx.h>
#include "Utils.h"



namespace RSA
{
    namespace Prime
    {
        using namespace Utils;
        
        //gen = random number generator
        //size = number of  bit of namber tested
        //precision = error of MIller-Rabin test = 1/2^(2* precision)
        //seed = seed for random number generator
        bool IsPrime(const BigInteger &number, unsigned long long seed, unsigned int size, unsigned int precision = 20);
        
        //gen = random number generator
        //size = number of  bit of prime generated
        //precision = error of MIller-Rabin test = 1/2^(2* precision)
        //seed = seed for random number generator
        BigInteger NextPrime(BigInteger current, unsigned long long seed, unsigned int size, unsigned int precision = 20);
    }
}

#endif /* defined(__RSA__Prime__) */
