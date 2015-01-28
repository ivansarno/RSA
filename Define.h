//
//  Define.h
//  RSA
//
//  Created by ivan sarno on 21/01/15.
//
//

#ifndef RSA_Define_h
#define RSA_Define_h

#include <cmath>
#include <time.h>
#include <stdlib.h>
#include "ttmath/ttmath.h" //arbitrary precision library




#define Intero ttmath::Int<32> //set int size of block: 32 for 1024 bit, 64 for 2048
#define RandNum rand() //random number generator
#define Primegen Primegenerator() //prime number generator
#define Precision 15 //precision of Miller-Rabin test
#define Randinit srand((int)time(NULL));
#define Distance 65536 // distance between prime number (2^16)




#endif
