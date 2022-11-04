CXXFLAGS = -std=c++17 -g -W -Wall -Wextra
Objects = mainTest.o RSA.o Utils.o Prime.o Test.o 
LibFlag = -L/usr/local/lib/ -lgmp -lgmpxx

Test : $(Objects)
	$(CXX) $(Objects) $(LibFlag) -o RSATest

Library :  CXXFLAGS = -std=c++17 -03 $(LibFlag)
Library :  RSA.o Utils.o Prime.o
	ar rcs RSALib.a $^

