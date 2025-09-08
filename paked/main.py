def unpack(string):
    leng = len(string)
    s_stack = [[]]
    m_stack = []
    for i in range(leng):
        if string[i].isdigit():
            m_stack.append(int(string[i]))
        elif string[i] == '[':
            s_stack.append([])
        elif string[i] == ']':
            last = s_stack.pop() * m_stack.pop()
            s_stack.append(s_stack.pop() + last)
        else:
            s_stack[-1].append(string[i])
    
    return s_stack[0], len(s_stack[0])

def find_common_prefix(seq_1, l_1, seq_2, l_2):
    for i in range(min(l_1, l_2)):
        if seq_1[i] != seq_2[i]:
            return seq_1[:i], i
    return seq_1[:i + 1], i + 1

def main():
    n = int(input())
    main_seq, len_main_seq = unpack(input())
    for _ in range(n - 1):
        main_seq, len_main_seq = find_common_prefix(main_seq, len_main_seq, *unpack(input()))
    print(''.join(main_seq))

if __name__ == '__main__':
    main()