def main():
    l, k = map(int, input().split())
    s = input()
    mapa = {}
    hash1 = hash2 = 0
    q1, q2 = 1000, 123
    r1, r2 = 1000007, 1000009
    Q1, Q2 = pow(q1, l - 1, r1), pow(q2, l - 1, r2)
    
    for i in range(l):
        hash1 = (hash1 * q1) % r1 + ord(s[i])
        hash2 = (hash2 * q2) % r2 + ord(s[i])
    mapa[(hash1, hash2)] = [0]
    
    i += 1
    x1, x2 = hash1, hash2
    for ch in s[i::]:
        x1 = ((x1 - ord(s[i - l]) * Q1) % r1 * q1 + ord(ch)) % r1
        x2 = ((x2 - ord(s[i - l]) * Q2) % r2 * q2 + ord(ch)) % r2
        if (x1, x2) not in mapa:
            mapa[(x1, x2)] = [i - l + 1]
        else:
            mapa[(x1, x2)].append(i - l + 1)
            if len(mapa[(x1, x2)]) == k:
                print(mapa[(x1, x2)][0], end=' ')
        i += 1


if __name__ == '__main__':
    main()