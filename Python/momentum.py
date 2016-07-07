m1 = float(input('m1: ').strip())
m2 = float(input('m2: ').strip())
v1 = float(input('v1: ').strip())
v2 = float(input('v2: ').strip())
stick = input('Do the objects stick together? (y/n) ').strip().lower() == 'y'
if stick:
    fv = (m1 * v1 + m2 * v2) / (m1 + m2)
    print('fv:', fv)
else:
    v3 = float(input('v3: ').strip())
    v4 = (m1 * v1 + m2 * v2 - m1 * v3) / m2
    print('v4:', v4)
