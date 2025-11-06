#include <iostream>


int main() {
    long a, b, s;
    std::cin >> a >> b >> s;

    long l = std::max(a, b) + 1;
    long r = s + std::min(a, b);

    while (l <= r) {
        long targetSide = l + (r - l) / 2;
        if ((targetSide - a) * (targetSide - b) > s) {
            r = targetSide - 1;
        } else if ((targetSide - a) * (targetSide - b) < s) {
            l = targetSide + 1;
        } else {
            std::cout << targetSide << '\n';
            return 0;
        }
    }

    std::cout << -1 << '\n';
}