#include <iostream>
#include <vector>

void eratos(std::vector<bool>& simples) {    
    for (int i = 2; i * i < simples.size(); i++) {
        if (simples[i]) {
            for (int j = i * i; j < simples.size(); j += i) {
                simples[j] = false;
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<bool> dp(n + 1, false);
    std::vector<bool> simples(n + 1, true);
    simples[0] = simples[1] = false;
    eratos(simples);
    for (int i = 1; i < dp.size(); ++i) {
        for (short j = 1; j < 4; ++j) {
            if (int id = i - j; id > -1 && !simples[id] && !dp[id]) {
                dp[i] = true;
                break;
            }
        }
    }
    std::cout << (dp.back() ? 1 : 2) << '\n';
}