//
//  Utils.h
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
    BigInteger message = generator.getBig(size) % modulus;
    BigInteger crypto = Encrypt(message, pub, modulus);
    BigInteger message1 = Decrypt(crypto, priv, modulus);
    bool result = (message1 == message);
    if(result)
        std::cout << "RSA test OK\n";
    else std::cout << "RSA test ERROR\n";
    return result;
}


bool RSA::CustomTest(unsigned int size, Utils::Generator *generator, int threads, unsigned int precision)
{
    if(size < 64 || generator == NULL)
    {
        std::cout << "RSA test invalid input\n";
        return false;
    }
    BigInteger pub, priv, modulus;
    
    ParallelKeygen(pub, priv, modulus, generator, size, threads, precision);
    BigInteger message = generator->getBig(size) % modulus;
    BigInteger crypto = Encrypt(message, pub, modulus);
    BigInteger message1 = Decrypt(crypto, priv, modulus);
    bool result = message1 == message;
    if(result)
        std::cout << "RSA test OK\n";
    else std::cout << "RSA test ERROR\n";
    return result;
}