#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Trie {
private:
    std::unordered_map<char, Trie*> children;
    bool isTerminal = false;

public:
    void addWord(const std::string& word) {
        Trie* node = this;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new Trie();
            }
            node = node->children[c];
        }
        node->isTerminal = true;
    }

    friend void dynamic(const std::string& str, const Trie* trie);
};

void dynamic(const std::string& str, const Trie* trie) {
    int n = str.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;
    
    for (int i = 0; i < n; ++i) {
        if (!dp[i]) continue;
        
        const Trie* node = trie;
        for (int j = i; j < n && node; ++j) {
            auto it = node->children.find(str[j]);
            if (it == node->children.end()) break;
            
            node = it->second;
            if (node->isTerminal) {
                dp[j + 1] = true;
            }
        }
    }
    
    std::cout << (dp[n] ? "YES" : "NO") << std::endl;
}

int main() {
    std::string str;
    std::cin >> str;
    
    int n;
    std::cin >> n;
    
    Trie trie;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        trie.addWord(word);
    }
    
    dynamic(str, &trie);
    return 0;
}