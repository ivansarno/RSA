//
//  Utils.h
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.5

#ifndef Test_h
#define Test_h

#include <iostream>
#include "RSA.h"
#include <stdint.h>


//automatic encryption/decryption test
// if message == 0, it is randomly generated
namespace RSA
{
    bool DefaultTest(unsigned int size = 1024);
    bool CustomTest(unsigned int size, Utils::Generator *generator, unsigned int precision, unsigned int distance = UINT32_MAX);
}




#endif /* Test_h */
