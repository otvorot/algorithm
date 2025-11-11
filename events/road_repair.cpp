#include <iostream>
#include <algorithm>
#include <vector>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    long long k;
    std::cin >> n >> m >> k;

    std::vector<std::pair<long long, long long>> origin(n + 2);
    std::vector<std::pair<int, short>> events;
    events.reserve(m * 2);

    for (int i = 1; i <= n; ++i) {
        std::cin >> origin[i].first;
    }

    int l, r;
    for (int i = 0; i < m; ++i) {
        std::cin >> l >> r;
        events.emplace_back(l, 1);
        events.emplace_back(r + 1, -1);
    }

    std::sort(
        events.begin(),
        events.end(),
        [] (const std::pair<int, short>& lhs, const std::pair<int, short>& rhs) {
            return lhs.first < rhs.first;
        }
    );

    l = events.front().first; r = events.back().first; int j = 0;
    long long mnozh = 0;

    for (int i = l; i < r; ++i) {
        if (i == events[j].first) {
            int p = j;
            while (p < events.size() - 1 && events[j].first == events[p].first) {
                mnozh += events[p].second;
                ++p;
            }
            j = p;
        }

        origin[i].second = mnozh;
    }

    std::sort(
        origin.begin() + l,
        origin.begin() + r,
        [] (const std::pair<long long, long long>& lhs, const std::pair<long long, long long>& rhs) {
            return lhs.second > rhs.second;
        }
    );

    long long final = 0;
    for (int i = l; i < r; ++i) {
        // std::cout << origin[i].first << ' ' << origin[i].second << '\n';
        long long diff = std::min(k, origin[i].first);
        k -= diff;
        origin[i].first -= diff;
        final += origin[i].first * origin[i].second;
    }

    std::cout << final << '\n';
}