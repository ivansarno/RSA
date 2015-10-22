//
//  RSA.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.2

#ifndef __RSA__RSA__
#define __RSA__RSA__

#include "Prime.h"
#define RSA_QCHECK

namespace RSA
{
    //using namespace Aux;
    using namespace Prime;
    
    //Keygen initializes keys and modulus, return true for success, false for error
    //size = number of bit of keys
    //gen = your subclass of RSA::Aux::Generator, for random number generation
    //precision = precision of Miller-Rabin primality test, error corrispond to 1/2^2*precision
    //distance = distance between prime numbers that compose the modulus of the keys, higher values for greater safety
    bool Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, Generator gen, unsigned int size, unsigned int precision = 20, unsigned long distance = UINT32_MAX);
    
    //return message encrypted or 0 for input error
    //size = number of bit of keys
    BigInteger Encrypt(const BigInteger &message, const BigInteger &pubkey, const BigInteger &modulus, unsigned int size);
    
    //return message decrypted or 0 for input error
    //size = number of bit of keys
    BigInteger Decrypt(const BigInteger &message, const BigInteger &privkey, const BigInteger &modulus, unsigned int size);
    
}

#endif /* defined(__RSA__RSA__) */
