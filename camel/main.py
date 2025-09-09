class Trie:
    def __init__(self):
        self.childs = {}
        self.ids = []
        
    def add(self, word, id):
        node = self
        for char in word:
            if char.isupper():
                if char not in node.childs:
                    node.childs[char] = Trie()
                node.childs[char].ids.append(id)
                node = node.childs[char]
    
    def get(self, word):
        node = self
        for char in word:
            if char not in node.childs:
                return ''
            node = node.childs[char]
        return node.ids


def main():
    n = int(input())
    arr = [0] * n
    trie = Trie()
    trie.ids.extend([i for i in range(n)])
    for i in range(n):
        arr[i] = input()
    arr.sort()
    for i in range(n):
        trie.add(arr[i], i)
    m = int(input())
    for _ in range(m):
        idxes = trie.get(input())
        for id in idxes:
            print(arr[id])

if __name__ == '__main__':
    main()