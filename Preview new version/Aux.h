//
//  Aux.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#ifndef __RSA__Aux__
#define __RSA__Aux__
#include <gmpxx.h>
#include <time.h>
#include <stdlib.h>

namespace Aux
{
    typedef mpz_class BigInteger;
    BigInteger pow( BigInteger base, BigInteger exp, int size);
    BigInteger mod_pow( BigInteger base, BigInteger exp, BigInteger mod, int size);
    BigInteger inverse(BigInteger n, BigInteger modulo);
    bool coprime (BigInteger a, BigInteger b);
    
    class Generator
    {
        Generator();
        
    public:
        BigInteger get(int size);
    };

}

#endif /* defined(__RSA__Aux__) */
