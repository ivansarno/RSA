//
//  Utils.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.4

#ifndef __RSA__Utils__
#define __RSA__Utils__
#include <gmpxx.h>
#include <time.h>
#include <stdlib.h>

namespace RSA
{
    namespace Utils
    {
        typedef mpz_class BigInteger;
        BigInteger pow(BigInteger base, BigInteger exp);
        BigInteger mod_pow(BigInteger base, BigInteger exp, const BigInteger &mod);
        BigInteger inverse(const BigInteger &number, const BigInteger &modulus, unsigned int size);
        bool coprime (BigInteger a, BigInteger b);
        BigInteger byte2biginteger(uint8_t *byte, unsigned int size);
        
        
        class Generator
        {
        public:
            Generator();
            virtual BigInteger get(unsigned int size);//return a positive BigInteger of size bit
        };
    }
}

#endif /* defined(__RSA__Utils__) */
