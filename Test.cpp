//
//  Utils.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.5

#include "Test.h"


bool RSA::DefaultTest(unsigned int size)
{
    if(size < 64)
    {
        std::cout << "RSA test invald input\n";
        return false;
    }
    BigInteger pub, priv, modulus;
    Utils::TestGenerator generator;
    Keygen(pub, priv, modulus, &generator, size);
    BigInteger message = generator.get(size) % modulus;
    BigInteger crypto = Encrypt(message, pub, modulus);
    BigInteger message1 = Decrypt(crypto, priv, modulus);
    bool result = (message1 == message);
    if(result)
        std::cout << "RSA test OK\n";
    else std::cout << "RSA test ERROR\n";
    return result;
}


bool RSA::CustomTest(unsigned int size, Utils::Generator *generator, unsigned int precision, unsigned int distance)
{
    if(size < 64 || generator == NULL)
    {
        std::cout << "RSA test invalid input\n";
        return false;
    }
    BigInteger pub, priv, modulus;
    
    Keygen(pub, priv, modulus, generator, size, precision, distance);
    BigInteger message = generator->get(size) % modulus;
    BigInteger crypto = Encrypt(message, pub, modulus);
    BigInteger message1 = Decrypt(crypto, priv, modulus);
    bool result = message1 == message;
    if(result)
        std::cout << "RSA test OK\n";
    else std::cout << "RSA test ERROR\n";
    return result;
}