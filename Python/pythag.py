from math import sqrt
import sys

a = None
b = None
c = None

if sys.argv[1].startswith('a='):
    a = float(sys.argv[1][2:])
elif sys.argv[2].startswith('a='):
    a = float(sys.argv[2][2:])

if sys.argv[1].startswith('b='):
    b = float(sys.argv[1][2:])
elif sys.argv[2].startswith('b='):
    b = float(sys.argv[2][2:])

if sys.argv[1].startswith('c='):
    c = float(sys.argv[1][2:])
elif sys.argv[2].startswith('c='):
    c = float(sys.argv[2][2:])

if c is None:
    print('c = ' + str(sqrt(a * a + b * b)))
else:
    if a is None:
        print('a = ' + str(sqrt(c * c - b * b)))
    else:
        print('b = ' + str(sqrt(c * c - a * a)))
