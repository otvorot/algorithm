#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>

using namespace std;

pair<vector<char>, int> unpack(const string& str) {
    stack<vector<char>> s_stack;
    stack<int> m_stack;
    s_stack.push(vector<char>());
    
    for (char c : str) {
        if (isdigit(c)) {
            m_stack.push(c - '0');
        } else if (c == '[') {
            s_stack.push(vector<char>());
        } else if (c == ']') {
            vector<char> last = s_stack.top();
            s_stack.pop();
            int multiplier = m_stack.top();
            m_stack.pop();
            
            vector<char> expanded;
            for (int i = 0; i < multiplier; i++) {
                expanded.insert(expanded.end(), last.begin(), last.end());
            }
            
            vector<char> top = s_stack.top();
            s_stack.pop();
            top.insert(top.end(), expanded.begin(), expanded.end());
            s_stack.push(top);
        } else {
            s_stack.top().push_back(c);
        }
    }
    
    vector<char> result = s_stack.top();
    return make_pair(result, result.size());
}

pair<vector<char>, int> find_common_prefix(const vector<char>& seq1, int l1, 
                                         const vector<char>& seq2, int l2) {
    int min_len = min(l1, l2);
    int i = 0;
    
    while (i < min_len && seq1[i] == seq2[i]) {
        i++;
    }
    
    vector<char> common_prefix(seq1.begin(), seq1.begin() + i);
    return make_pair(common_prefix, i);
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    string input;
    getline(cin, input);
    
    auto main_unpacked = unpack(input);
    vector<char> main_seq = main_unpacked.first;
    int len_main_seq = main_unpacked.second;
    
    for (int i = 0; i < n - 1; i++) {
        getline(cin, input);
        auto current_unpacked = unpack(input);
        auto result = find_common_prefix(main_seq, len_main_seq, 
                                       current_unpacked.first, current_unpacked.second);
        main_seq = result.first;
        len_main_seq = result.second;
    }
    
    for (char c : main_seq) {
        cout << c;
    }
    cout << endl;
    
    return 0;
}