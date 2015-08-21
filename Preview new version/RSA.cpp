//
//  RSA.cpp
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#include "RSA.h"

using namespace RSA;

BigInteger RSA::Encrypt(BigInteger message, BigInteger pubkey, BigInteger modulo, int size)
{
    //if(message != NULL && pubkey > 1 && modulo > 1)
        return Aux::mod_pow(message, pubkey, modulo, size);
    //else return -1;
}

BigInteger RSA::Decrypt(BigInteger message, BigInteger privkey, BigInteger modulo, int size)
{
    //if(message != NULL && modulo > 1 && privkey > 1)
        return Aux::mod_pow(message, privkey, modulo, size);
    //else return -1;
}


//check the compliance with security standard
bool E_check(BigInteger E, BigInteger Phi)
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

void RSA::Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulo, RSA::Aux::Generator gen, int size, int precision, unsigned long distance)
{
   
    BigInteger primeP= Prime::Generates(gen, size/2); //generates prime number for key mod
    BigInteger primeQ= Prime::Generates(gen, size/2);
    
    while (!Q_check(primeQ,primeP, distance)) //make sure it is appropriate for security standards
    {
        primeQ= Prime::Generates(gen, size/2);
    }
    
    BigInteger Phi = (primeP-1) * (primeQ-1);
    BigInteger N = primeP * primeQ; //Mod of key
    
    BigInteger E = gen.get(size);
    E = E % N;//public key
    
    
    while (!E_check(E, Phi)) //make sure it is appropriate for security standards
    {
        E++;
    }
    pubkey = E;
    modulo = N;
    
    privkey = Aux::inverse(E, Phi); //private key
    
}
