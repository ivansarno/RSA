//
//  RSA.cpp
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.5

#include "RSA.h"

using namespace RSA;

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

bool RSA::Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision, unsigned long distance)
{
    if(size < 64 || precision < 2)
        return false;
    

    
    BigInteger primeP = Prime::NextPrime(gen->get(size/2), time(NULL), size/2, precision);
    BigInteger primeQ = Prime::NextPrime(gen->get(size/2), time(NULL), size/2, precision);
    
    
    while(!Q_check(primeP, primeQ, distance))
    {
        primeQ = Prime::NextPrime(gen->get(size/2), time(NULL), size/2, precision);
    }
    
    BigInteger Phi = (primeP-1) * (primeQ-1);
    modulus = primeP * primeQ; //Mod of key
    
    pubkey = gen->get(size);
    pubkey = pubkey % modulus;//public key
 

    while (!E_check(pubkey, Phi)) //make sure it is appropriate for security standards
    {
        pubkey++;
    }

    privkey = Utils::inverse(pubkey, Phi, size); //private key
    
    return true;
}


int RSA::Foult(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Utils::Generator *gen, unsigned int size, unsigned int precision, unsigned long distance)
{
    if(size < 64 || precision < 2)
        return false;
    auto fault = 0;
    
    
    BigInteger primeP = Prime::NextPrime(gen->get(size/2), time(NULL), size/2, precision);
    BigInteger primeQ = Prime::NextPrime(gen->get(size/2), time(NULL), size/2, precision);
    
    
    while(!Q_check(primeP, primeQ, distance))
    {
        primeQ = Prime::NextPrime(gen->get(size/2), time(NULL), size/2, precision);
        
    }
    
    BigInteger Phi = (primeP-1) * (primeQ-1);
    modulus = primeP * primeQ; //Mod of key
    
    pubkey = gen->get(size);
    pubkey = pubkey % modulus;//public key
    
    
    while (!E_check(pubkey, Phi)) //make sure it is appropriate for security standards
    {
        pubkey++;
        fault++;
    }
    
    privkey = Utils::inverse(pubkey, Phi, size); //private key
    
    return fault;
}

