from math import *

def getPolyProp(n, p=30):
    l = p / n
    c = 360 / n
    ap = (l * 0.5) / tan(radians(c * 0.5))
    A = 0.5 * ap * p
    print("Side Length: " + str(l))
    print("Central Angle: " + str(c))
    print("Apothem: " + str(ap))
    print("Area: " + str(A))
    print("Area to Perimater Ratio: " + str(A / p))

if __name__ == '__main__':
    for i in range(3, 23):
        print("Polygon with", i, "sides: ")
        getPolyProp(i)
        print()

    print("Polygon with", 1000, "sides: ")
    getPolyProp(1000)
    print()
