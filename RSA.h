//
//  RSA.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.0

#ifndef __RSA__RSA__
#define __RSA__RSA__

#include "Aux.h"
#include "Prime.h"

namespace RSA
{
    //using namespace Aux;
    using namespace Prime;
    
    //Keygen initializes keys and modulus
    //size = number of bit of keys
    //gen = your subclass of RSA::Aux::Generator, for random number generation
    //precision = precision of Miller-Rabin primality test, error corrispond to 1/2^2*precision
    //distance = distance between prime numbers that compose the modulus of the keys, higher values for greater safety
    void Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, Generator gen, int size, int precision = 20, unsigned long distance = UINT32_MAX);
    BigInteger Encrypt(BigInteger message, BigInteger pubkey, BigInteger modulus, int size);
    BigInteger Decrypt(BigInteger message, BigInteger privkey, BigInteger modulus, int size);
    
}

#endif /* defined(__RSA__RSA__) */
