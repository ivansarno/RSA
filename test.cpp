#include <iostream>
#include "RSA.h"
#include <assert.h>

using namespace RSA;





int main()
{
	BigInteger pub, priv, modulus;
    Generator gen;
    int size = 1024;
    Keygen(pub, priv, modulus, gen, size);

    BigInteger message = 300300;
    BigInteger crypto = Encrypt(message, pub, modulus, size);
    BigInteger message1 = Decrypt(crypto, priv, modulus, size);

	
	
	std::cout << crypto << "\n\n\n" << message1 << "\n\n\n";// << priv << "\n";

	return 0;
}