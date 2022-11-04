//
//  RSA.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno
/*
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
//Version V.4.0

#ifndef __RSA__RSA__
#define __RSA__RSA__

#include "Prime.h"
#include <thread>


namespace RSA
{
    //using namespace Utils;
    //using namespace Prime;
    using Utils::BigInteger;
    
    //Keygen initializes keys and modulus, return true for success, false for error
    //size = number of bit of keys
    //gen = your subclass of RSA::Utils::Generator, for random number generation
    //precision = precision of Miller-Rabin primality test, error corrispond to 1/2^2*precision
    bool Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, Utils::Generator *gen, unsigned int size, unsigned int precision = 20);
    
    //Parallel version of Keygen, initializes keys and modulus, return true for success, false for error
    //size = number of bit of keys
    //gen = your subclass of RSA::Utils::Generator, for random number generation
    //precision = precision of Miller-Rabin primality test, error corrispond to 1/2^2*precision
    //threads = number of threads to use
    bool ParallelKeygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, Utils::Generator *gen, unsigned int size, int threads=4, unsigned int precision = 20);
    
    //return message encrypted or 0 for input error
    BigInteger Encrypt(const BigInteger &message, const BigInteger &pubkey, const BigInteger &modulus);
    
    //return message decrypted or 0 for input error
    BigInteger Decrypt(const BigInteger &message, const BigInteger &privkey, const BigInteger &modulus);
}

#endif /* defined(__RSA__RSA__) */
