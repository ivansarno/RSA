//
//  Utils.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.4

#include "Test.h"


bool RSA::DefaultTest(unsigned long message, unsigned int size)
{
    if(message < 1 || size < 64)
    {
        std::cout << "RSA test invald input\n";
        return false;
    }
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


bool RSA::CustomTest(unsigned long message, unsigned int size, Utils::Generator generator, unsigned int precision, unsigned int distance)
{
    if(message < 1 || size < 64)
    {
        std::cout << "RSA test invald input\n";
        return false;
    }
    BigInteger pub, priv, modulus;
    
    Keygen(pub, priv, modulus, generator, size, precision, distance);
    BigInteger crypto = Encrypt(message, pub, modulus, size);
    BigInteger message1 = Decrypt(crypto, priv, modulus, size);
    bool result = message1 == message;
    if(result)
        std::cout << "RSA test OK\n";
    else std::cout << "RSA test ERROR\n";
    return result;
}