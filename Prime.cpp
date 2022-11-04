//
//  Prime.cpp
//  RSA
//
//  Created by ivan sarno on 28/07/15.
//  Copyright (c) 2015 ivan sarno
/*
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
//Version V.4.1

#include "Prime.h"

using namespace RSA;
using namespace RSA::Prime;

//component of Miller-Rabin primality test
inline void MRscomposition(const BigInteger &N, unsigned int &w, BigInteger &z)
{
    z = N - 1;
    w = 0;
    while(BigInteger(z&1) == 0)
    {
        w++;
        z >>= 1;
    }
}

inline bool MRpredicate1 (const BigInteger &y, const BigInteger &z, const BigInteger &N)
{
    return (Utils::mod_pow(y,z,N)==1);
}

bool MRpredicate2(const BigInteger &y, const BigInteger &N, const BigInteger &z, const unsigned int &w)
{
    unsigned int i = 0;
    BigInteger pow2 = 1;
    bool cond = BigInteger(Utils::mod_pow(y, z, N)) == BigInteger(N-1);
    
    while (!cond && i < w)
    {
        i++;
        pow2 <<= 1;
        cond = (Utils::mod_pow(y, pow2*z, N) == BigInteger(N-1));
    }
    
    return i != w;
}

bool MRtest(const BigInteger &N, unsigned int size, unsigned int precision, TestGenerator *gen)  //Miller-rabin test for prime number
{
    unsigned int w; BigInteger z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;//default result
    unsigned i=0;
    
    
    BigInteger y;
    
    while (ris && i < precision)
    {
        y = gen->getBig(size) % N;
        
        while(y<2)//avoid random number < 2
        {
            y = (y + gen->getBig(64)) % N;
        }
        ris = (coprime(y,N)) && (MRpredicate1(y, z, N)|| MRpredicate2(y, N, z, w));
        i++;
    }
    return ris;
}

//extract a random number and search a early prime
BigInteger Prime::NextPrime(BigInteger current, unsigned int size, unsigned int precision)
{
    if(current < 2)
        return 2;
    
    auto gen = TestGenerator();
    if (BigInteger(current & 1)==0)
        current++;
    
    while (!MRtest(current, size, precision, &gen))
    {
        current +=2;
    }
    
    return current;
}

bool Prime::IsPrime(const BigInteger &number, unsigned int size, unsigned int precision)
{
    if(number == 2)
        return true;
    if(BigInteger(number & 1) == 0 || number < 2)
        return false;
    auto gen = TestGenerator();
    return MRtest(number, size, precision, &gen);
}

//extract a random number and search a early prime, to use with threads
void Prime::ThreadsNextPrime(BigInteger *current, unsigned int size, unsigned int precision)
{
    if(*current < 2)
    {
        *current = 2;
        return;
    }
    
    auto gen = TestGenerator();
    if (BigInteger(*current & 1)==0)
        *current += 1;
    
    while (!MRtest(*current, size, precision, &gen))
    {
        *current +=2;
    }
}

//Version for worker routine
bool WorkersMRtest(const BigInteger &N, unsigned int size, unsigned int precision, std::atomic<bool> *not_found, TestGenerator *gen)  //Miller-rabin test for prime number
{
    unsigned int w; BigInteger z;
    
    MRscomposition(N,w,z);
    
    bool ris =true;//default result
    unsigned i=0;
    
    
    BigInteger y;
    
    while (*not_found && ris && i < precision)
    {
        y = gen->getBig(size) % N;
        
        while(y<2)//avoid random number < 2
        {
            y = (y + gen->getBig(64)) % N;
        }
        ris = coprime(y,N) && (MRpredicate1(y, z, N)|| (MRpredicate2(y, N, z, w)));
        i++;
    }
    return ris;
}

void WorkerRoutine(BigInteger *current, int size, unsigned int precision, int id, int increment, std::atomic<bool> *not_found)
{
    BigInteger number = *current + 2*id;
    auto gen = TestGenerator();
    
    while (*not_found && !WorkersMRtest(number, size, precision, not_found, &gen))
    {
        number += increment;
    }
    
    bool expected = true;
    if(not_found->compare_exchange_strong(expected, false))
    {
        *current = number;
    }
}

//extract a random number and search a early prime using more threads
void Prime::ParallelNextPrime(BigInteger *current, unsigned int size, unsigned int precision, int threads)
{
    if(*current < 2)
    {
        *current = 2;
        return;
    }
    if(BigInteger(*current & 1) == 0)
        (*current)++;
    
    std::atomic<bool> not_found;
    not_found = true;
    int i;
    std::thread *workers = new std::thread[threads];
    
    for(i = 0; i<threads; i++)
    {
        workers[i] = std::thread(WorkerRoutine,current, size, precision, i, 2*threads, &not_found);
    }
    
    for(i = 0; i<threads; i++)
    {
        workers[i].join();
    }
    
    delete[] workers;
}
