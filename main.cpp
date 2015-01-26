//
//  main.cpp
//  RSA
//
//  Created by ivan sarno on 21/01/15.
//  Copyright (c) 2015 ivan sarno. All rights reserved.
//

#include <iostream>
#include "Define.h"
#include "RSA_fun.h"

int main(int argc, const char * argv[])
{
    
    Randinit
    Key Pubkey,Privkey;
    
    RSA_key_create(Pubkey, Privkey);
    
    Intero m = RandNum;
    
    std::cout << m << "\n";
    
    
    
    Intero c = RSA_encrypt(m,Pubkey);
    
    std::cout << c << "\n";
    
    
   // std::cout << Privkey.E << "\n";
    
    Intero ris = RSA_decrypt(c,Privkey);
    
    std::cout << ris << "\n";
    
   // int t;
    
   // std::cin >> t;
    
   // std::cout << MRtest(t) << "\n";
    
    
    return 0;
}
