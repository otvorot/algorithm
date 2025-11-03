#include <iostream>
#include <string>
#include <vector>

struct Trie {
    Trie* childs[26] {nullptr};
    bool terminal = false;

    void add(const std::string& inputToken) {
        Trie* now = this;
        for (short i = 0; i < inputToken.size(); ++i) {
            short id = inputToken[i] - 'a';
            if (now->childs[id] == nullptr) {
                now->childs[id] = new Trie();
            }
            now = now->childs[id];
        }
        now->terminal = true;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string base, token;
    Trie root;
    short n;
    std::cin >> base;
    std::cin >> n;

    while (n > 0) {
        std::cin >> token;
        root.add(token);
        --n;
    }

    std::vector<short> dp(base.size() + 1, -1);
    short i = 0, j;
    while (i < base.size()) {
        j = i;
        Trie* now = &root;
        Trie* next = now->childs[base[j] - 'a'];
        while (j < base.size() && next) {
            if (next->terminal) {
                dp[j + 1] = i;
            }
            now = next;
            ++j;
            next = now->childs[base[j] - 'a'];
        }
        ++i;
        while (i < base.size() && dp[i] == -1) {
            ++i;
        }
    }

    std::vector<short> spaces;
    i = dp.size() - 1;
    while (i) {
        spaces.push_back(dp[i]);
        i = dp[i];
    }

    auto it = spaces.rbegin() + 1;
    for (short i = 0; i < base.size(); ++i) {
        if (it != spaces.rend() && *it == i) {
            std::cout << ' ';
            ++it;
        }
        std::cout << base[i];
    }

    //std::cout << 'n';
}