import sys

precision = 2

def p(x1, x2):
    print(('{:.' + str(precision) + 'f}, {:.' + str(precision) + 'f},').format(x1, x2))

def printTextureCoords(width, height, textwidth, textheight):
    for i in range(width):
        for j in range(height):
            x1 = i / textwidth
            y1 = j / textheight
            x2 = (i + 1) / textwidth
            y2 = (j + 1) / textheight
            
            #First Triangle
            
            p(x1, y1)
            p(x2, y1)
            p(x1, y2)
            
            # Second Triangle
            
            p(x1, y2)
            p(x2, y1)
            p(x2, y2)
    
    print('Number of points:', width * height * 6)
    print('Precision:', precision)

if __name__ == '__main__':
    if len(sys.argv) >= 5:
        printTextureCoords(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4]))
    else:
        print('using default (3,2,4,2)')
        printTextureCoords(3, 2, 4, 2)
