#include <iostream>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long long d = 0, n = 0;
    int buckets[26] = {0};

    char input = 'f';
    while (true) {
        std::cin.get(input);
        if (input == '\n') break;
        ++buckets[input - 'a'];
        ++n;
    }

    for (short i = 0; i < 26; ++i) {
        if (long long c = buckets[i]; c > 1) {
            d += c * (c - 1) / 2;
        }
    }

    std::cout << 1 + (n * (n - 1) / 2) - d << '\n';
    return 0;
}