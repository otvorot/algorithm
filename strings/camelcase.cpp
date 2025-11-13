#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

class Trie {
    unordered_map<char, Trie*> childs;
    vector<int> ids;
    
public:
    vector<int>& getIds() { return ids; }
    
    void add(const string& word, int id) {
        Trie* node = this;
        for (char c : word) {
            if (isupper(c)) {
                if (!node->childs[c]) node->childs[c] = new Trie();
                node->childs[c]->ids.push_back(id);
                node = node->childs[c];
            }
        }
    }
    
    vector<int> get(const string& word) {
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
    cin >> n; cin.ignore();
    
    vector<string> arr(n);
    Trie trie;
    
    // Объединенный цикл: чтение строк и добавление индексов
    for (int i = 0; i < n; i++) {
        getline(cin, arr[i]);
        trie.getIds().push_back(i);
    }
    
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) trie.add(arr[i], i);
    
    cin >> m; cin.ignore();
    while (m--) {
        string query;
        getline(cin, query);
        for (int id : trie.get(query)) cout << arr[id] << endl;
    }
}