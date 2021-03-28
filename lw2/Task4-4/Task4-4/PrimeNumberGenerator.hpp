#pragma once
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    int boolPrimeSize = upperBound + 1;
    vector<bool> isPrime(boolPrimeSize, false);

    int squareLimit = (int)sqrt((long double)upperBound);
    isPrime[2] = true;
    isPrime[3] = true;

    int i, j;
    int x2 = 0, y2;
    int n;
    for (i = 1; i <= squareLimit; ++i)
    {
        x2 += 2 * i - 1;
        y2 = 0;
        for (j = 1; j <= squareLimit; ++j)
        {
            y2 += 2 * j - 1;

            n = 4 * x2 + y2;
            if ((n <= upperBound) && (n % 12 == 1 || n % 12 == 5))
                isPrime[n] = !isPrime[n];

            n -= x2;
            if ((n <= upperBound) && (n % 12 == 7))
                isPrime[n] = !isPrime[n];

            n -= 2 * y2;
            if ((i > j) && (n <= upperBound) && (n % 12 == 11))
                isPrime[n] = !isPrime[n];
        }
    }
    
    for (i = 5; i <= squareLimit; ++i)
    {
        if (isPrime[i]) 
        {
            n = i * i;
            for (j = n; j <= upperBound; j += n)
                isPrime[j] = false;
        }
    }

    set<int> primeNumbers;
    for (i = 2; i <= upperBound; ++i) 
    {
        if (isPrime[i])
            primeNumbers.insert(i);
    }
	return primeNumbers;
}