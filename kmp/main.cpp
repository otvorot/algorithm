#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string text, pattern, replace;
    std::cin >> text >> pattern >> replace;
    
    std::string s = pattern + '#' + text;
    std::vector<int> pi(pattern.size());
    std::vector<char> res;
    int k = 0;
    
    for (int i = 1; i < s.size(); i++) {
        res.push_back(s[i]);
        
        while (k > 0 && s[k] != s[i]) {
            k = pi[k - 1];
        }
        
        if (s[k] == s[i]) k++;
        if (i < pattern.size()) pi[i] = k;
        
        if (k == pattern.size()) {
            res.erase(res.end() - pattern.size(), res.end());
            res.insert(res.end(), replace.begin(), replace.end());
            k = pi[k - 1];
        }
    }
    
    std::cout << std::string(res.begin() + pattern.size(), res.end());
    return 0;
}