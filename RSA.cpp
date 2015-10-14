//
//  RSA.cpp
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.1

#include "RSA.h"

using namespace RSA;

BigInteger RSA::Encrypt(const BigInteger &message, const BigInteger &pubkey, const BigInteger &modulus, unsigned int size)
{
    //if(message != NULL && pubkey > 1 && modulus > 1)
    power_buffer_init(size);
    BigInteger result = Aux::mod_pow(message, pubkey, modulus);
    power_buffer_release();
    return result;
}

BigInteger RSA::Decrypt(const BigInteger &message, const BigInteger &privkey, const BigInteger &modulus, unsigned int size)
{
    //if(message != NULL && modulus > 1 && privkey > 1)
    power_buffer_init(size);
    BigInteger result = Aux::mod_pow(message, privkey, modulus);
    power_buffer_release();
    return result;
}


//check the compliance with security standard
bool E_check(const BigInteger &E, const BigInteger &Phi)
{
    return coprime(E,Phi) && (E-1!=Phi/4) && (E-1!=Phi/2) && E > 1;
}

bool Q_check(BigInteger Q, BigInteger P, unsigned long distance)
{
    BigInteger dif = (P-Q);
    abs(dif);
    P=(P-1)/2;
    Q=(Q-1)/2;
    
    return coprime(P,Q) && (dif > distance);
}

void RSA::Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulus, RSA::Aux::Generator gen, unsigned int size, unsigned int precision, unsigned long distance)
{
    power_buffer_init(size);
    
    BigInteger primeP= Prime::Generates(gen, size/2); //generates prime number for key mod
    BigInteger primeQ= Prime::Generates(gen, size/2);

#ifdef QCHECK
    while (!Q_check(primeQ,primeP, distance)) //make sure it is appropriate for security standards
    {
        primeQ= Prime::Generates(gen, size/2);
    }
#endif
    
    BigInteger Phi = (primeP-1) * (primeQ-1);
    BigInteger N = primeP * primeQ; //Mod of key
    
    BigInteger E = gen.get(size);
    E = E % N;//public key
 
#ifdef TEMP
    while ((E < 2) || (!coprime(E,Phi))) //make sure it is appropriate for security standards
    {
        E++;
    }
#endif
#ifdef ECHECK
    while (!E_check(E, Phi)) //make sure it is appropriate for security standards
    {
        E++;
    }
#endif
    
    pubkey = E;
    modulus = N;
    
    privkey = Aux::inverse(E, Phi); //private key
    
    power_buffer_release();
}
