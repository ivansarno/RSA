//
//  RSA_fun.h
//  RSA
//
//  Created by ivan sarno on 21/01/15.
//
//

#ifndef __RSA__RSA_fun__
#define __RSA__RSA_fun__

#include "Define.h"
#include "Euclide.h"
#include "aux_fun.h"

#define Inverse(a,m) inverso(a,m)

typedef struct
{
    Intero E; //key
    Intero N; //modulo
} Key;


Intero RSA_encrypt(Intero message, Key Pubkey);
Intero RSA_decrypt(Intero message, Key Privkey);
void RSA_Privkey_create(Key Pubkey,Key Prekey,Key &Privkey);//generate Private Key from Prekey and Public Key
void RSA_Pubkey_create(Key Prekey, Key &Pubkey);//generate Public Key from Prekey
void RSA_Prekey_create(Key &Prekey);//take uninitialized Key variable and generate temporaly data for key generation


#endif /* defined(__RSA__RSA_fun__) */
