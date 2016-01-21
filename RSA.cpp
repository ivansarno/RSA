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
//Version V.4.0

#include "RSA.h"

using namespace RSA;
using namespace Prime;

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
inline bool Q_check(BigInteger Q, BigInteger P, unsigned long distance)
{
    BigInteger dif = abs(P-Q);
    P=(P-1)>>1;
    Q=(Q-1)>>1;
    
    return (dif > distance) && coprime(P,Q);
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
inline void DualRoutine(BigInteger &primeP, BigInteger &primeQ, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision, unsigned long distance)
{
    primeP = gen->getBig(size/2);
    auto worker = std::thread(TNextPrime, &primeP, size/2, precision);
    primeQ = Prime::NextPrime(gen->getBig(size/2), size/2, precision);
    worker.join();
    
    
    while(!Q_check(primeP, primeQ, distance))
    {
        primeQ = gen->getBig(size/2);
        Prime::PNextPrime(&primeQ, size/2, precision);
    }
}

//multithread prime extraction routine
inline void ParallelRoutine(BigInteger &primeP, BigInteger &primeQ, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision, unsigned long distance, int threads)
{
    primeP = gen->getBig(size/2);
    auto worker = std::thread(PNextPrime, &primeP, size/2, precision, threads/2);
    primeQ = gen->getBig(size/2);
    Prime::PNextPrime(&primeQ, size/2, precision, (threads-threads/2));
    worker.join();
    
    
    while(!Q_check(primeP, primeQ, distance))
    {
        primeQ = gen->getBig(size/2);
        Prime::PNextPrime(&primeQ, size/2, precision, threads);
    }
}

bool RSA::Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision, unsigned long distance)
{
    if(size < 64 || precision < 2)
        return false;
    
    BigInteger primeP = Prime::NextPrime(gen->getBig(size/2), size/2, precision);
    BigInteger primeQ = Prime::NextPrime(gen->getBig(size/2), size/2, precision);
    
    
    while(!Q_check(primeP, primeQ, distance))
    {
        primeQ = Prime::NextPrime(gen->getBig(size/2), size/2, precision);
    }
    
    return KeygenRoutine(primeP, primeQ, pubkey, privkey, modulus, gen, size);
}

bool RSA::ParallelKeygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Utils::Generator *gen, unsigned int size, int threads, unsigned int precision, unsigned long distance)
{
    if(threads < 2)
        return Keygen(pubkey, privkey, modulus, gen, size, precision, distance);
    if(size < 64 || precision < 2)
        return false;
    
    BigInteger primeP, primeQ;
    
    if(threads < 4)
        DualRoutine(primeP, primeQ, gen, size, precision, distance);
    else ParallelRoutine(primeP, primeQ, gen, size, precision, distance, threads);
    
    
    return KeygenRoutine(primeP, primeQ, pubkey, privkey, modulus, gen, size);
}






