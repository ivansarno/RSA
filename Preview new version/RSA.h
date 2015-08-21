//
//  RSA.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#ifndef __RSA__RSA__
#define __RSA__RSA__

#include "Aux.h"
#include "Prime.h"

namespace RSA
{
    //using namespace Aux;
    using namespace Prime;
    
    void Keygen(BigInteger &pubkey, BigInteger &privkey, BigInteger &modulo, Generator gen, int size, int precision = 20, unsigned long distance = UINT32_MAX);
    BigInteger Encrypt(BigInteger message, BigInteger pubkey, BigInteger modulo, int size);
    BigInteger Decrypt(BigInteger message, BigInteger privkey, BigInteger modulo, int size);
    
}

#endif /* defined(__RSA__RSA__) */
