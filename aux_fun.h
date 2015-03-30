//
//  aux_fun.h
//  RSA
//
//  Created by ivan sarno on 22/01/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
// version V.2.0

#ifndef __RSA__aux_fun__
#define __RSA__aux_fun__

#include "Define.h"


Intero fastexp( Intero base, Intero esp); //exponentiation
Intero modexp( Intero base, Intero esp, Intero mod); //modular exponentiation
//Miller-Rabin primality test
bool MRpredicate1 (Intero y, Intero z, Intero N);
bool MRpredicate2(Intero y, Intero N, Intero z, Intero w);
bool MRtest(Intero N); //Miller-Rabin test for prime number
void MRscomposition(Intero N, Intero &w, Intero &z);
//
Intero Primegenerator(); //built-in prime number generator
Intero inverso(Intero n, Intero Modulo); //modular inverse
bool coprime (Intero a,  Intero b); //return true if MCD(a,b) == 1

char *randstring(); // random number generator, only for test 



#endif /* defined(__RSA__aux_fun__) */
