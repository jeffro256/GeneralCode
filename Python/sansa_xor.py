def getContiguousArrays(arr):
    subarrays = []
    
    for i in range(len(arr)):
        for j in range(i + 1, len(arr) + 1):
            subarrays.append(arr[i:j])
            
    return subarrays

def arrayXOR(arr):
    res = 0
    
    for i in arr:
        res ^= i
        
    return res

def main():
    tests = int(input())
    
    for i in range(tests):
        input()
        nums = list(map(int, input().split(' ')))
        
        carrs = getContiguousArrays(nums)
        flat_carrs = [arrayXOR(x) for x in carrs]
        answer = arrayXOR(flat_carrs)
        print(answer)

if __name__ == '__main__':
    main()

