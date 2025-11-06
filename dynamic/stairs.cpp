#include <iostream>
#include <vector>

int main() {
    short n;
    std::cin >> n;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));
    dp[0].assign(n + 1, 1);

    for (short i = 1; i < dp.size(); ++i) {
        for (short j = 1; j < dp[0].size(); ++j) {
            dp[i][j] = dp[i][j - 1];
            if (i >= j) {
                dp[i][j] += dp[i - j][j - 1];
            }
        }
    }

    std::cout << dp.back().back() << '\n';
}