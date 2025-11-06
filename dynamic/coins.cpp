#include <iostream>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();
    int prev[3] {};
    int now[3] {};
    int temp[3] {};

    while (n > 0) {
        --n;
        char input;

        // читаем now
        for (short i = 0; i < 3; ++i) {
            std::cin.get(input);
            if (input == 'W') {
                now[i] = -10;
            } else if (input == 'C') {
                now[i] = 1;
            } else {
                now[i] = 0;
            }
        }
        std::cin.ignore();

        // запись temp
        temp[0] = (now[0] == -10) ? -10 : now[0] + std::max(prev[0], prev[1]);
        temp[1] = (now[1] == -10) ? -10 : now[1] + std::max({prev[0], prev[1], prev[2]});
        temp[2] = (now[2] == -10) ? -10 : now[2] + std::max(prev[2], prev[1]);

        // проверка
        if(temp[0] < 0 && temp[1] < 0 && temp[2] < 0) break;

        // swapaem
        prev[0] = temp[0];
        prev[1] = temp[1];
        prev[2] = temp[2];
    }

    std::cout << std::max({prev[0], prev[1], prev[2]}) << '\n';
}