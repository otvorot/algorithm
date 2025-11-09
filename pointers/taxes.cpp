#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n;

    std::vector<std::pair<long, long>> power;
    power.reserve(n);

    long t1, t2;
    for (int i = 0; i < n; ++i) {
        std::cin >> t1 >> t2;
        power.emplace_back(t1, t2);
    }

    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::cin >> t1;
        auto it = std::upper_bound(
            power.begin(),
            power.end(),
            std::make_pair(t1, 0),
            [] (const std::pair<long, long>& lhs, const std::pair<long, long>& rhs) {
                return lhs.first < rhs.first;
            }
        );

        if (t1 == (it - 1)->first) {
            std::cout << t1 * (it - 2)->second << '\n';
        } else {
            std::cout << t1 * (it - 1)->second << '\n';
        }
    }
}