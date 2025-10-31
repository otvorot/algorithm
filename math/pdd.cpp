#include <iostream>
#include <cmath>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long x, y, xe, ye;
    std::cin >> x >> y >> xe >> ye;

    long long left = (x - xe == 0) ? 0 : 1;
    long long up = (y - ye == 0) ? 0 : 1;

    long long ans = (std::abs(x - xe) - 1) * left * 3 + (std::abs(y - ye) - 1) * up * 3 + left * up;
    std::cout << ans << '\n';
}