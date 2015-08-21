#include <iostream>
#include "RSA.h"
#include <assert.h>

using namespace RSA;





int main()
{
	BigInteger pub, priv, modulo;
    Generator gen;
    int size = 1024;
    Keygen(pub, priv, modulo, gen, size);
    
    assert(priv < modulo);
    assert(pub < modulo);
    BigInteger message = 300300;
    BigInteger crypto = Encrypt(message, pub, modulo, size);
    BigInteger message1 = Decrypt(crypto, priv, modulo, size);

	
	
	std::cout << crypto << "\n\n\n" << message1 << "\n\n\n";// << priv << "\n";
	//std::cout << sizeof(Intero);*/

	return 0;
}