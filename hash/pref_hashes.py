def hashes(string, now_r, arr, q, R, l, r):
    if not now_r:
        hash = 0
        arr.append(hash)
        for i in range(r):
            hash = (hash * q + ord(string[i])) % R
            arr.append(hash)
        now_r.append(r)
    if now_r[-1] < r:
        hash = arr[-1]
        for i in range(now_r[-1], r):
            hash = (hash * q + ord(string[i])) % R
            arr.append(hash)
        now_r.append(r)
    return (arr[r] - pow(q, r - l + 1, R) * arr[l - 1]) % R

if __name__ == '__main__':
    q = int(input())
    R = int(input())
    s = input()
    n = int(input())
    now_r = []
    arr = []
    for _ in range(n):
        l, r = map(int, input().split())
        print(hashes(s, now_r, arr, q, R, l, r))