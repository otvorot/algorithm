#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>

class Trie {
    std::unordered_map<char, Trie*> childs;
    std::vector<int> ids;
    
public:
    std::vector<int>& getIds() { return ids; }
    
    void add(const std::string& word, int id) {
        Trie* node = this;
        for (char c : word) {
            if (isupper(c)) {
                if (!node->childs[c]) node->childs[c] = new Trie();
                node->childs[c]->ids.push_back(id);
                node = node->childs[c];
            }
        }
    }
    
    std::vector<int> get(const std::string& word) {
        Trie* node = this;
        for (char c : word) {
            if (!node->childs[c]) return {};
            node = node->childs[c];
        }
        return node->ids;
    }
    
    ~Trie() {
        for (auto& [c, ptr] : childs) delete ptr;
    }
};

int main() {
    int n, m;
    std::cin >> n; std::cin.ignore();
    
    std::vector<std::string> arr(n);
    Trie trie;
    
    
    for (int i = 0; i < n; i++) {
        getline(std::cin, arr[i]);
        trie.getIds().push_back(i);
    }
    
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) trie.add(arr[i], i);
    
    std::cin >> m; std::cin.ignore();
    while (m--) {
        std::string query;
        getline(std::cin, query);
        for (int id : trie.get(query)) std::cout << arr[id] << '\n';
    }

    return 0;
}