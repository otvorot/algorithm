#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>


std::pair<std::vector<char>, int> unpack(const std::string& str) {
    std::stack<std::vector<char>> s_stack;
    std::stack<int> m_stack;
    s_stack.push(std::vector<char>());
    
    for (char c : str) {
        if (isdigit(c)) {
            m_stack.push(c - '0');
        } else if (c == '[') {
            s_stack.push(std::vector<char>());
        } else if (c == ']') {
            std::vector<char> last = s_stack.top();
            s_stack.pop();
            int multiplier = m_stack.top();
            m_stack.pop();
            
            std::vector<char> expanded;
            for (int i = 0; i < multiplier; i++) {
                expanded.insert(expanded.end(), last.begin(), last.end());
            }
            
            std::vector<char> top = s_stack.top();
            s_stack.pop();
            top.insert(top.end(), expanded.begin(), expanded.end());
            s_stack.push(top);
        } else {
            s_stack.top().push_back(c);
        }
    }
    
    std::vector<char> result = s_stack.top();
    return make_pair(result, result.size());
}

std::pair<std::vector<char>, int> find_common_prefix(const std::vector<char>& seq1, int l1, 
                                         const std::vector<char>& seq2, int l2) {
    int min_len = std::min(l1, l2);
    int i = 0;
    
    while (i < min_len && seq1[i] == seq2[i]) {
        i++;
    }
    
    std::vector<char> common_prefix(seq1.begin(), seq1.begin() + i);
    return std::make_pair(common_prefix, i);
}

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();
    
    std::string input;
    getline(std::cin, input);
    
    auto main_unpacked = unpack(input);
    std::vector<char> main_seq = main_unpacked.first;
    int len_main_seq = main_unpacked.second;
    
    for (int i = 0; i < n - 1; i++) {
        getline(std::cin, input);
        auto current_unpacked = unpack(input);
        auto result = find_common_prefix(main_seq, len_main_seq, 
                                    current_unpacked.first, current_unpacked.second);
        main_seq = result.first;
        len_main_seq = result.second;
    }
    
    for (char c : main_seq) {
        std::cout << c;
    }
    std::cout << '\n';
    
    return 0;
}