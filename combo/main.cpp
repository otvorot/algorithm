#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


std::unordered_map<char, std::string> keyboard = {
    {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
    {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
};

void back(const std::vector<std::string>& x, int index, std::string& res) {
    if (index == x.size()) {
        std::cout << res << " ";
        return;
    }
    for (char c : x[index]) {
        res.push_back(c);
        back(x, index + 1, res);
        res.pop_back();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<std::string> base;
    char input;
    while (std::cin.get(input)) {
        base.push_back(keyboard[input]);
    }
    
    std::string start;
    back(base, 0, start);
    
    return 0;
}