from math import *

n = int(input("Number of sides: "))
s = float(input("Side length: "))
c = 360.0 / n
a = s / (2 * tan(radians(c / 2)))
A = a * s * n / 2
print("Area:", A)
