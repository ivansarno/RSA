//
//  aux_fun.cpp
//  RSA
//
//  Created by ivan sarno on 22/01/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//
// version V.2.0

#include "aux_fun.h"



Intero fastexp(Intero base, Intero esp)
{
	if (esp == 0)
		return 1;
	if (esp == 1)
		return base;
	else
	{
		Intero i = 1;
		int j = 0;
		Intero *tempris = new Intero[Block_size]; //buffer for intermediate results
		tempris[0] = base;
		while (i < esp)
		{
			tempris[j+1] = tempris[j] * tempris[j];
			j++;
			i *= 2;
		}
		Intero result = 1;
		while (esp > 0)
		{
			if (esp - i >= 0)
			{
				result *= tempris[j];
				esp -= i;
			}
			j--;
			i /= 2;
		}
        delete [] tempris;
		return result;
	}
}

Intero modexp(Intero base, Intero esp, Intero mod)
{
	if (esp == 0)
		return 1;
	if (esp == 1)
		return base;
	else
	{
		Intero i = 1;
		int j = 0;
		Intero *tempris = new Intero [Block_size];
		tempris[0] = base;
		while (i < esp)
		{
			tempris[j+1] = (tempris[j] * tempris[j]) % mod;
			j++;
			i *= 2;
		}
		Intero result = 1;
		while (esp > 0)
		{
			if (esp - i >= 0)
			{
				result = (result * tempris[j]) % mod;
				esp -= i;
			}
			j--;
			i /= 2;
		}
        delete[] tempris;
		return result;
	}
}

bool MRpredicate1 (Intero y, Intero z, Intero N)
{
    if (modexp(y,z,N)==1)
        return true;
    else return false;
}

bool MRpredicate2(Intero y, Intero N, Intero z, Intero w)
{
    Intero i=0;
    bool cond = (modexp(y,fastexp(2,i)*z, N) == N-1);
    
    while (!cond && i < w)
    {
        i++;
        cond = (modexp(y,fastexp(2,i)*z, N) == N-1);
    }
    
    if (i==w)
        return false;
    else return true;
        
}

bool MRtest(Intero N)  //Miller-rabin test for prime number
{
    Intero w; Intero z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;
    int i=0;
    
    
    Intero y;
    
    while (ris && i < Precision)
    {
        y = RandNum;
        y= y % N;
        while(y<2)
        {
            y = RandNum;
            y= y % N;
        }
        ris = (coprime(y,N)) && (MRpredicate1(y, z, N)|| MRpredicate2(y, N, z, w));
        i++;
    }
    return ris;
}

void MRscomposition(Intero N, Intero &w, Intero &z)
{
    Intero i=1;
    Intero acc=2;
    N--;
    Intero r;
    
    while (acc < N)
    {
        r=N/acc;
        if ((N%acc==0) && (r%2==1))
        {
            w=i;
            z=r;
        }
        i++;
        acc = acc * 2;
    }
}

//extract a random number and search a early prime
Intero Primegenerator()
{
    Intero P = RandNum;
    if (P%2==0)
        P++;
    
    while (!MRtest(P))//primality test
    {
        P = P+2;
    }
    
    return P;
}

/*
 implementation of Extended Euclide algorithm to find the inverse of a numbere in module and coprime number
 */

typedef struct
{
    Intero x;
    Intero y;
    Intero z;
} triple;




triple ExtendedEuclide(Intero a, Intero b)
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

Intero inverso(Intero n,Intero Modulo)
{
    triple ris = ExtendedEuclide(n,Modulo);
    if (ris.y<0)
        ris.y=Modulo+ris.y;
    
    return  ris.y;
}

bool coprime (Intero a, Intero b)
{
    triple temp = ExtendedEuclide(a, b);
    if (temp.x == 1)
        return true;
    else return false;
}

//generates a string of random digit, isn't sure, for test only
char *randstring()
{
	int size = (Block_size *3)/20 -1;
	char * rs = new char[size + 1];
	int i;
	for (i = 0; i < size; i++)
		rs[i] = (char) (rand() % 10 + 48);

		rs[size] = '\0';
		return rs;
}


