#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    std::vector<long> days(n);
    std::vector<long> diff(n + 1);
    long output = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> days[i];
        int l = i + 1;
        int r = days[i] + i;
        if (r <= l) continue;

        diff[l] += 1;
        diff[std::min(r, n)] -= 1;
    }

    for (int i = 0; i < n; ++i) {
        diff[i] += diff[std::max(0, i - 1)];
        output += days[i] * diff[i];
    }

    // for (auto& x : diff) {
    //     std::cout << x << ' ';
    // }
    std::cout << output << '\n';
}