//
//  Euclide.cpp
//  RSA
//
//  Created by ivan sarno on 21/01/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#include "Euclide.h"

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
