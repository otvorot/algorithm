class Trie:
    def __init__(self):
        self.child = {}
        self.terminal = 0
 
        
    def add_word(self, word):
        node = self
        for char in word:
            node.child[char] = node.child.get(char, Trie())
            node = node.child[char]
        node.terminal = True
        
 
def dynamic(string, trie):
    string_l = len(string)
    dp = [False] * (string_l + 1)
    dp[0] = True
    i = 0

    node = trie
    while i < string_l:
        while dp[i] == False and i < string_l:
            i += 1
        for j in range(i, string_l):
            child = node.child.get(string[j], 0)
            if child:
                node = child
                if node.terminal:
                    dp[j + 1] = True
 
            else:
                break

        i += 1
        node = trie

    print('YES' if dp[-1] else 'NO')
 
                
 
    
 
def main():
    string = input()
    n = int(input())
    trie = Trie()
    for _ in range(n):
        trie.add_word(input())

    dynamic(string, trie)
 
    
 
if __name__ == '__main__':
    main()