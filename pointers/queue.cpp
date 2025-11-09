#include <iostream>
#include <vector>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, target;
    std::cin >> n >> target;

    std::vector<int> prefix {0};
    prefix.reserve(n * 2 + 2);

    int token;
    for (int i = 0; i < n; ++i) {
        std::cin >> token;
        if (token >= target) {
            prefix.emplace_back(prefix.back() + 1);
        } else {
            prefix.emplace_back(prefix.back());
        }
    }

    std::cin >> m;
    int l = 0, r;
    char comand;
    for (int i = 0; i < m; ++i) {
        std::cin >> comand;
        if (comand == '1') {
            std::cin >> token;
            if (token >= target) {
                prefix.emplace_back(prefix.back() + 1);
            } else {
                prefix.emplace_back(prefix.back());
            }


        } else if (comand == '2') {
            ++l;


        } else {
            std::cin >> token;
            r = l + token;
            std::cout << prefix[r] - prefix[l] << '\n';
        }
    }
}