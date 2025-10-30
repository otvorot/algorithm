#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, k;
    std::cin >> n >> k;

    if (k == 0 || n % 10 == 0) {
        
    } else if (n % 10 == 5) {
        n += 5;
    } else {
        int initial_steps = std::min((long long)4, k);
        for (int i = 0; i < initial_steps; i++) {
            n += n % 10;
            k--;
        }

        if (k > 0) {
            long long cycles = k / 4;
            int remaining = k % 4;
            
            n += cycles * 20;
            
            for (int i = 0; i < remaining; i++) {
                n += n % 10;
            }
        }
    }

    std::cout << n << '\n';
    return 0;
}