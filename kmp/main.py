def main():
    text = input()
    pattern = input()
    replace = list(input())
    len_pattern = len(pattern)
    fine_txt = pattern + '#' + text
    len_txt = len(fine_txt)
    dp = [0] * len_pattern
    last_match = 0
    res = []
    for i in range(1, len_txt):
        res.append(fine_txt[i])
        k = last_match
        while k > 0 and fine_txt[k] != fine_txt[i]:
            k = dp[k - 1]
        if fine_txt[k] == fine_txt[i]:
            k += 1
        if i < len_pattern:
            dp[i] = k
        last_match = k
        if k == len_pattern:
            res = res[:-len_pattern] + replace

    print(*res[len_pattern::], sep='')


if __name__ == '__main__':
    main()