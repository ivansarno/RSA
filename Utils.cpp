//
//  Utils.cpp
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
//Version V.3.4

#include "Utils.h"

using namespace RSA;
using namespace Utils;

//random number generator, only for test
Utils::Generator::Generator()
{
    srand((int)time(NULL));
}

BigInteger Utils::Generator::get(unsigned int size)
{
    size /= 8;
    uint8_t *byte = new uint8_t[size];
    int i;
    for (i = 0; i < size; i++)
        byte[i] = rand();

    BigInteger n = byte2biginteger(byte, size);
    delete[] byte;
    return n;
};


BigInteger Utils::pow(BigInteger base, BigInteger exp)
{
    BigInteger resoult = 1;

    while(exp > 0)
    {
        if((exp & 1) == 1)
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
        if((exp & 1) == 1)
            resoult = (base * resoult) % mod;
        base = (base * base) % mod;
        exp >>=1;
    }

    return resoult;
}

typedef struct
{
    BigInteger x;//greatest common divisisor
    BigInteger y;//inverse of a mod b
    BigInteger z;//intermediate value
} triple;

triple ExtendedEuclide(BigInteger a, BigInteger b)
{
    triple result;
    triple temp;

    if (b == 0)
    {
        result.x = a;
        result.y = 1;
        result.z = 0;

        return result;
    }
    else temp = ExtendedEuclide(b, a % b);

    result.x = temp.x;
    result.y = temp.z;
    result.z = temp.y - ((a / b) * temp.z);

    return result;
}

//iterative version of extended euclide
void IExtendedEuclide(const BigInteger &a, const BigInteger &b, BigInteger &MCD, BigInteger &inverse, unsigned int size)
{
    if (b == 0)
    {
        MCD = a;
        inverse = 1;
        return;
    }

    unsigned long i = 0;
    BigInteger temp, intermediate;
    BigInteger *buffer_a = new BigInteger[size]; //buffer for intermediates values
    BigInteger *buffer_b = new BigInteger[size];
    buffer_a[0] = a;
    buffer_b[0] = b;

    while(buffer_b[i] > 0) //find greatest common divisor
    {
        i++;
        buffer_a[i] = buffer_b[i-1];
        buffer_b[i] = buffer_a[i-1] % buffer_b[i-1];
    }

    MCD = buffer_a[i];
    intermediate = 1;
    temp = 0;

    while(i > 0) //inverse calculation from intermediates values
    {
        i--;
        inverse = temp;
        temp = intermediate - ((buffer_a[i] / buffer_b[i]) * temp);
        intermediate = inverse;
    }

    delete [] buffer_a;
    delete [] buffer_b;
}

BigInteger Utils::inverse(const BigInteger &number, const BigInteger &modulus, unsigned int size)
{
    if (modulus == 0)
    {
        return 0;
    }

    long i = 0;
    BigInteger result, temp, intermediate;
    BigInteger *buffer_a = new BigInteger[size];
    BigInteger *buffer_b = new BigInteger[size];

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
    auto res = BigInteger(z);
    mpz_clear(z);
    return res;
}
