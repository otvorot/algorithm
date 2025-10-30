#include <iostream>
#include <vector>
#include <string>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short n, m;
    std::string input;
    std::cin >> n >> m;

    std::vector<std::vector<char>> matrix(n, std::vector<char>(m));
    std::vector<int> rows(n);
    std::vector<int> cols(m);
    for (short i = 0; i < n; ++i) {
        std::cin >> input;
        for (short j = 0; j < m; ++j) {
            matrix[i][j] = input[j];
            if (input[j] == '-') {
                --rows[i];
                --cols[j];
            } else if (input[j] == '+') {
                ++rows[i];
                ++cols[j];
            } else {
                ++rows[i];
                --cols[j];
            }
        }
    }

    int best = -1000000;
    for (short i = 0; i < n; ++i) {
        for (short j = 0; j < m; ++j) {
            int diff = rows[i] - cols[j];
            if (matrix[i][j] == '?') {
                diff -= 2;
            }
            best = std::max(best, diff);
        }
    }

    std::cout << best << '\n';
}