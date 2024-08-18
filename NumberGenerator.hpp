#pragma once

#include <cstdlib>

class NumberGenerator
{
public:
    static int nextPrime()
    {
        while (true)
        {
            if (isPrime(currentPrime))
            {
                return currentPrime++;
            }
            currentPrime++;
        }
    }

    static int nextFibonacci()
    {
        int next = currentFib + currentFib2;
        currentFib = currentFib2;
        currentFib2 = next;

        return next;
    }

    static int nextRandomInt()
    {
        return rand();
    }

private:
    static bool isPrime(int number)
    {
        if (number <= 1)
        {
            return false;
        }

        for (int i = 2; i * i <= number; i++)
        {
            if (number % i == 0)
            {
                return false;
            }
        }

        return true;
    }

private:
    static int currentFib;
    static int currentFib2;
    static int currentPrime;
};

int NumberGenerator::currentFib = 0;
int NumberGenerator::currentFib2 = 1;
int NumberGenerator::currentPrime = 2;