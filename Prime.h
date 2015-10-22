//
//  Prime.h
//  RSA
//
//  Created by ivan sarno on 28/07/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.2

#ifndef __RSA__Prime__
#define __RSA__Prime__
#include <gmpxx.h>
#include "Aux.h"


//using namespace Aux;

namespace RSA
{
    namespace Prime
    {
        using namespace Aux;
        
        //gen = random number generator
        //size = number of  bit of nember tested
        //precision = error of MIller-Rabin test = 1/2^(2* precision)
        bool IsPrime(const BigInteger &number, Generator &gen, unsigned int size, unsigned int precision = 20);
        
        //gen = random number generator
        //size = number of  bit of prime generated
        //precision = error of MIller-Rabin test = 1/2^(2* precision)
        BigInteger Generates(Generator &gen, unsigned int size, unsigned int precision = 20);
    }
}

#endif /* defined(__RSA__Prime__) */
