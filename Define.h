//
//  Define.h
//  RSA
//
//  Created by ivan sarno on 21/01/15.
//
//
// version V.2.0

#ifndef RSA_Define_h
#define RSA_Define_h

#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <gmpxx.h>


#define Block_size 1024
#define Intero mpz_class 
#define Primegen Primegenerator() //prime number generator
#define Precision 15 //precision of Miller-Rabin test
#define RandNum  mpz_class(randstring(), 10)   //random number generator
#define Randinit srand((int)time(NULL)); 
#define Distance 65536 // distance between prime number (2^16)


#endif
