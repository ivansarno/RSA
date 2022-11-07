//
//  RSA.cpp
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
//Version V.4.1

#include "RSA.h"

using namespace RSA;
using namespace Prime;

#define PRIME_SIZE size/2

BigInteger RSA::Encrypt(const BigInteger &message, const BigInteger &pubkey, const BigInteger &modulus)
{
    if(modulus > 1 && pubkey > 1)
    {
        BigInteger result = Utils::mod_pow(message, pubkey, modulus);
        return result;
    }
    return 0;
}

BigInteger RSA::Decrypt(const BigInteger &message, const BigInteger &privkey, const BigInteger &modulus)
{
    if(modulus > 1 && privkey > 1)
    {
        BigInteger result = Utils::mod_pow(message, privkey, modulus);
        return result;
    }
    return 0;
}


//check the compliance with security standard
inline bool E_check(const BigInteger &E, const BigInteger &Phi)
{
    BigInteger quarter = Phi>>2;
    BigInteger half = Phi>>1;
    BigInteger prec = E-1;
    return coprime(E,Phi) && (prec!=quarter) && (prec!=half) && E > 1;
}

//check the compliance with security standard
inline bool Q_check(BigInteger Q, BigInteger P, unsigned long size)
{
    BigInteger dif = abs(P-Q);
    P=(P-1)>>1;
    Q=(Q-1)>>1;
    
    return (bitSize(dif) > size/2) && coprime(P,Q);
}

//creates the keys from 2 prime numbers
inline bool KeygenRoutine(BigInteger &primeP, BigInteger &primeQ, BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Utils::Generator *gen, unsigned int size)
{
    BigInteger Phi = (primeP-1) * (primeQ-1);
    modulus = primeP * primeQ; //Mod of key
    
    pubkey = gen->getBig(size);
    pubkey = pubkey % modulus;//public key
    
    
    while (!E_check(pubkey, Phi)) //make sure it is appropriate for security standards
    {
        pubkey++;
    }
    
    privkey = Utils::inverse(pubkey, Phi, size); //private key
    
    return true;
}

//prime extraction routine for 2 threads
inline void DualRoutine(BigInteger &primeP, BigInteger &primeQ, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision)
{
    primeP = gen->getBig(PRIME_SIZE);
    auto worker = std::thread(ThreadsNextPrime, &primeP, PRIME_SIZE, precision);
    primeQ = Prime::NextPrime(gen->getBig(PRIME_SIZE), PRIME_SIZE, precision);
    worker.join();
    
    
    while(!Q_check(primeP, primeQ, PRIME_SIZE))
    {
        primeQ = gen->getBig(PRIME_SIZE);
        Prime::ParallelNextPrime(&primeQ, PRIME_SIZE, precision);
    }
}

//multithread prime extraction routine
inline void ParallelRoutine(BigInteger &primeP, BigInteger &primeQ, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision, int threads)
{
    primeP = gen->getBig(PRIME_SIZE);
    auto worker = std::thread(ParallelNextPrime, &primeP, PRIME_SIZE, precision, threads/2);
    primeQ = gen->getBig(PRIME_SIZE);
    Prime::ParallelNextPrime(&primeQ, PRIME_SIZE, precision, (threads-threads/2));
    worker.join();
    
    
    while(!Q_check(primeP, primeQ, PRIME_SIZE))
    {
        primeQ = gen->getBig(PRIME_SIZE);
        Prime::ParallelNextPrime(&primeQ, PRIME_SIZE, precision, threads);
    }
}

bool RSA::Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision)
{
    if(size < 64 || precision < 2)
        return false;
    
    BigInteger primeP = Prime::NextPrime(gen->getBig(PRIME_SIZE), PRIME_SIZE, precision);
    BigInteger primeQ = Prime::NextPrime(gen->getBig(PRIME_SIZE), PRIME_SIZE, precision);
    
    
    while(!Q_check(primeP, primeQ, PRIME_SIZE))
    {
        primeQ = Prime::NextPrime(gen->getBig(PRIME_SIZE), PRIME_SIZE, precision);
    }
    
    return KeygenRoutine(primeP, primeQ, pubkey, privkey, modulus, gen, size);
}

bool RSA::ParallelKeygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Utils::Generator *gen, unsigned int size, int threads, unsigned int precision)
{
    if(threads < 2)
        return Keygen(pubkey, privkey, modulus, gen, size, precision);
    if(size < 64 || precision < 2)
        return false;
    
    BigInteger primeP, primeQ;
    
    if(threads < 4)
        DualRoutine(primeP, primeQ, gen, size, precision);
    else ParallelRoutine(primeP, primeQ, gen, size, precision, threads);
    
    
    return KeygenRoutine(primeP, primeQ, pubkey, privkey, modulus, gen, size);
}






