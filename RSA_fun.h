//
//  RSA_fun.h
//  RSA
//
//  Created by ivan sarno on 21/01/15.
//
//
// version V.2.0

#ifndef __RSA__RSA_fun__
#define __RSA__RSA_fun__

#include "aux_fun.h"

typedef struct
{
    Intero E; //key
    Intero N; //modulo
} Key;

Intero RSA_encrypt(Intero message, Key Pubkey); //return -1 if parameter are illegal
Intero RSA_decrypt(Intero message, Key Privkey); //return -1 if parameter are illegal
void RSA_key_create(Key &Pubkey, Key &Privkey);//take uninitialized Key variable and generate Public and Private Key

//subfunction
bool E_check(Intero E, Intero Phi);
bool Q_check(Intero Q, Intero P);


#endif /* defined(__RSA__RSA_fun__) */
