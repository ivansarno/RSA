//
//  Aux.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.2

#include "Test.h"


bool RSA::test(unsigned long message, unsigned int size)
{
    BigInteger pub, priv, modulus;
    Generator gen;
    Keygen(pub, priv, modulus, gen, size);
    BigInteger crypto = Encrypt(message, pub, modulus, size);
    BigInteger message1 = Decrypt(crypto, priv, modulus, size);
    bool result = message1 == message;
    if(result)
        std::cout << "RSA test OK\n";
    else std::cout << "RSA test ERROR\n";
    return result;
}
