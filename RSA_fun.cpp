//
//  RSA_fun.cpp
//  RSA
//
//  Created by ivan sarno on 21/01/15.
//
//

#include "RSA_fun.h"

Intero RSA_encrypt(Intero message, Key Pubkey)
{
    return modexp(message, Pubkey.E, Pubkey.N);
}

Intero RSA_decrypt(Intero message, Key Privkey)
{
    return modexp(message, Privkey.E, Privkey.N);
}

void RSA_Privkey_create(Key Pubkey,Key Prekey,Key &Privkey)
{
    Privkey.E = Inverse(Pubkey.E, Prekey.E);
    Privkey.N = Pubkey.N;
}






void RSA_Pubkey_create(Key Prekey, Key &Pubkey)
{
    Pubkey.N = Prekey.N;
    
    Intero E = RandNum;
    E = E % Prekey.E;

    
    while (!coprime(E, Prekey.E))
    {
        E++;
    }
    Pubkey.E = E;
}

void RSA_Prekey_create(Key &Prekey)
{
    Intero primeP= Primegen;
    Intero primeQ= Primegen;
    
    Prekey.E = (primeP-1) * (primeQ-1);
    Prekey.N = primeP * primeQ;
}


