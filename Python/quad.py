from math import sqrt

a = float(input('a: '))
b = float(input('b: '))
c = float(input('c: '))

des = b * b - 4 * a * c

if des < 0:
    print("No real solutions")
elif des == 0:
    x = -b / (2 * a)
    print('x =', x)
else:
    x1 = (-b + sqrt(des)) / (2 * a)
    x2 = (-b - sqrt(des)) / (2 * a)

    print('x =', str(x1) + ',', x2)
