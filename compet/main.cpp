#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short chr[] = {-1, 1};
    short input;
    int now = 0;
    unsigned n, best = 0;
    std::cin >> n;
    std::unordered_map<int, int> mapa = {
        {0, -1}
    };
    mapa.reserve(n);

    for (unsigned i = 0; i != n; ++i) {
        std::cin >> input;
        now += chr[input];
        if (mapa.contains(now)) {
            best = std::max(best, (i - mapa[now]));
        } else {
            mapa[now] = i;
        }
    }

    std::cout << best << '\n';
    return 0;
}