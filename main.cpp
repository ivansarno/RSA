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
    srand(time(NULL));
    
    Key Pubkey, Prekey, Privkey;

    RSA_Prekey_create(Prekey);
    
    RSA_Pubkey_create(Prekey, Pubkey);
    
    std::cout << Pubkey.E << "\n";
    
    Intero c = RSA_encrypt(3477,Pubkey);
    
    std::cout << c << "\n";
    
   RSA_Privkey_create(Pubkey, Prekey, Privkey);
    
    std::cout << Privkey.E << "\n";
    
    std::cout << RSA_decrypt(c,Privkey) << "\n";
    
   // int t;
    
   // std::cin >> t;
    
   // std::cout << MRtest(t) << "\n";
    
    return 0;
}
