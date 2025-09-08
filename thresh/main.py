def checkpairs(n, array, mid):
    l, r = 0, 1
    result = 0

    while r < n:
        while array[r] - array[l] > mid:
            l += 1
        result += (r - l)
        r += 1
    
    return result



def bin_search(n, array, target):
    l, r = 0, array[-1] - array[0]
    while l < r:
        mid = l + (r - l) // 2
        if checkpairs(n, array, mid) >= target:
            r = mid
        else:
            l = mid + 1
    return l



if __name__ == '__main__':
    n = int(input())
    array = list(map(int, input().split()))
    k = int(input())

    array.sort()

    print(bin_search(n, array, k))