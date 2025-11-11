#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long sumA = 0;
    std::cin >> n;

    std::vector<std::pair<long long, long long>> sA(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> sA[i].first;
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> sA[i].second;
        sumA += sA[i].second;
    }

    std::sort(sA.begin(), sA.end());
    
    long long prefixA = 0;
    int i = -1;
    while (prefixA * 2 < sumA) {
        ++i;
        prefixA += sA[i].second;
    }

    long long& median = sA[i].first;

    long long outputSum = 0;
    for (int i = 0; i < n; ++i) {
        outputSum += std::abs(sA[i].first - median) * sA[i].second;
    }

    std::cout << median << ' ' << outputSum << '\n';
}