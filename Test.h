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
//Version V.4.0

#ifndef Test_h
#define Test_h

#include <iostream>
#include "RSA.h"
#include <stdint.h>


//automatic encryption/decryption test
namespace RSA
{
    bool DefaultTest(unsigned int size = 1024);
    bool CustomTest(unsigned int size, Utils::Generator *generator, int threads = 1, unsigned int precision=20, unsigned int distance = UINT32_MAX);
}




#endif /* Test_h */
