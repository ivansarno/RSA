//
//  Aux.cpp
//  RSA
//
//  Created by ivan sarno on 21/08/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#include "Aux.h"

using namespace RSA;
using namespace Aux;

//random number generator, only for test
Aux::Generator::Generator()
{
    srand((int)time(NULL));
}

BigInteger Aux::Generator::get(int size)
{
    size = (size *3)/20 -1;
    char *rs = new char[size + 1];
    int i;
    for (i = 0; i < size; i++)
            rs[i] = (char) (rand() % 10 + 48);
        
    rs[size] = '\0';
    return mpz_class(rs, 10);
};


BigInteger Aux::pow(BigInteger base, BigInteger exp, int size)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    else
    {
        BigInteger i = 1;
        int j = 0;
        BigInteger *tempris = new BigInteger[size]; //buffer for intermediate results
        tempris[0] = base;
        while (i < exp)
        {
            tempris[j+1] = tempris[j] * tempris[j];
            j++;
            i *= 2;
        }
        BigInteger result = 1;
        while (exp > 0)
        {
            if (exp - i >= 0)
            {
                result *= tempris[j];
                exp -= i;
            }
            j--;
            i /= 2;
        }
        delete [] tempris;
        return result;
    }
}

BigInteger Aux::mod_pow(BigInteger base, BigInteger exp, BigInteger mod, int size)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    else
    {
        BigInteger i = 1;
        int j = 0;
        BigInteger *tempris = new BigInteger [size];
        tempris[0] = base;
        while (i < exp)
        {
            tempris[j+1] = (tempris[j] * tempris[j]) % mod;
            j++;
            i *= 2;
        }
        BigInteger result = 1;
        while (exp > 0)
        {
            if (exp - i >= 0)
            {
                result = (result * tempris[j]) % mod;
                exp -= i;
            }
            j--;
            i /= 2;
        }
        delete[] tempris;
        return result;
    }
}

typedef struct
{
    BigInteger x;
    BigInteger y;
    BigInteger z;
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

BigInteger Aux::inverse(BigInteger n,BigInteger modulo)
{
    triple ris = ExtendedEuclide(n,modulo);
    if (ris.y<0)
        ris.y=modulo+ris.y;
    
    return  ris.y;
}

bool Aux::coprime(BigInteger a, BigInteger b)
{
    triple temp = ExtendedEuclide(a, b);
    if (temp.x == 1)
        return true;
    else return false;
}