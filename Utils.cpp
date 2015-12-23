//
//  Utils.cpp
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.5

#include "Utils.h"

using namespace RSA;
using namespace Utils;

//random number generator, only for test
Utils::TestGenerator::TestGenerator()
{
    mpz_init(rand);
    seed = time(NULL);
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);
}

//random number generator, only for test
Utils::TestGenerator::TestGenerator(unsigned long long seed)
{
    mpz_init(rand);
    this->seed = seed;
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, this->seed);
}

Utils::TestGenerator::~TestGenerator()
{
    mpz_clear(rand);
    gmp_randclear(rstate);
}

BigInteger Utils::TestGenerator::get(unsigned int size)
{
    mpz_urandomb(rand, rstate, size);
    return BigInteger(rand);
};


BigInteger Utils::pow(BigInteger base, BigInteger exp)
{
    BigInteger resoult = 1;
    
    while(exp > 0)
    {
        if(BigInteger(exp & 1) == 1)
            resoult *= base;
        base *= base;
        exp >>=1;
    }
    
    return resoult;
}

BigInteger Utils::mod_pow(BigInteger base, BigInteger exp, const BigInteger &mod)
{
    BigInteger resoult = 1;
    
    while(exp > 0)
    {
        if(BigInteger(exp & 1) == 1)
            resoult = (base * resoult) % mod;
        base = (base * base) % mod;
        exp >>=1;
    }
    
    return resoult;
}



BigInteger Utils::inverse(const BigInteger &number, const BigInteger &modulus, unsigned int size)
{
    if (modulus == 0)
    {
        return 0;
    }
    
    long i = 0;
    BigInteger result, temp, intermediate;
    BigInteger *buffer_a = new BigInteger[size+1];
    BigInteger *buffer_b = new BigInteger[size+1];
    
    buffer_a[0] = number;
    buffer_b[0] = modulus;
    
    while(buffer_b[i] > 0) //find intermediate values of greatest common divisor
    {
        i++;
        buffer_a[i] = buffer_b[i-1];
        buffer_b[i] = buffer_a[i-1] % buffer_b[i-1];
    }
    
    result = 1;
    intermediate = 1;
    temp = 0;
    
    while(i > 0) //inverse calculation from intermediates values
    {
        i--;
        result = temp;
        temp = intermediate - ((buffer_a[i] / buffer_b[i]) * temp);
        intermediate = result;
    }
    
    delete [] buffer_a;
    delete [] buffer_b;
    
    if(result > 0)
        return result;
    else return modulus + result;
}

bool Utils::coprime (BigInteger a, BigInteger b)
{
    if (b == 0)
        return false;
    
    BigInteger temp;
    long i = 0;
    
    while(b > 0) //find greatest common divisor
    {
        i++;
        temp = b;
        b = a % b;
        a = temp;
    }
    
    return a == 1;
}


BigInteger Utils::byte2biginteger(uint8_t *byte, unsigned int size)
{
    mpz_t z;
    mpz_init(z);
    mpz_import(z, size, 1, sizeof(byte[0]), 0, 0, byte);
    BigInteger r = BigInteger(z);
    mpz_clear(z);
    return r;
}