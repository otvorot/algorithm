#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> matrix(n * m, 0);
    std::vector<int> dp(n * m, 1);
    std::vector<std::tuple<int, int>> values(n * m);
    int best = 1;

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int id = i * m + j;
            std::cin >> matrix[id];
            values[id] = {matrix[id], id};
        }
    }

    std::sort(values.begin(), values.end());

    for (int i = 0; i < values.size(); ++i) {
        auto [val, coord] = values[i];
        int x = coord / m;
        int y = coord % m;

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int ncoord = nx * m + ny;
                if (matrix[ncoord] == val - 1) {
                    dp[coord] = std::max(dp[coord], dp[ncoord] + 1);
                    best = std::max(best, dp[coord]);
                }
            }
        }
    }

    std::cout << best << '\n';
}