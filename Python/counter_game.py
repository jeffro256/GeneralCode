T = int(input())

def playgame(N):
    turns = 0
    
    while N != 1:
        if isPowerOfTwo(N):
            N /= 2
        else:
            po2 = 1
            while (po2 < N):
                po2 <<= 1
            po2 >>= 1
            
            N -= po2

    print("Richard" if turns % 2 == 0 else "Louise")

def isPowerOfTwo(num):
    return num > 0 and (num & (num - 1) == 0)

for _ in range(T):
    playgame(int(input()))

