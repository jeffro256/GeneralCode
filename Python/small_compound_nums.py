#!/usr/bin/python3

# Start Imports
from math import ceil, sqrt
from sys import argv
# End Imports

def getFactors(n):
    factors = set()

    for i in range(1, int(sqrt(n)) + 1):
        if n % i == 0:
            factors.add(i)
            factors.add(n / i)

    return factors

def getPrimeFactors(n):
    factors = []

    while n != 1:
        for i in range(2, int(n+1)):
            if n % i == 0:
                factors.append(i)
                n //= i
                break

    return factors
    
def main():
    max_factors = 0
    n = 1

    while True:
        try:
            factors = getPrimeFactors(n) if (len(argv) > 1 and argv[1] == '-prime') else getFactors(n)

            if len(factors) > max_factors:
                print(n)
                max_factors += 1

            n += 1
        except KeyboardInterrupt:
            break

if __name__ == '__main__':
    main()