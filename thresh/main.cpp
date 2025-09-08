#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> array;
unsigned n, k;

unsigned checkPairs(int mid) {
    auto l = array.begin(), r = l + 1;
    unsigned result = 0;
    while (r != array.end()) {
        while (*r - *l > mid) {
            ++l;
        }
        result += r - l;
        ++r;
    }
    return result;
}

unsigned binSearch(unsigned target) {
    unsigned mid, l = 0, r = array.back() - array.front();
    while (l < r) {
        mid = l + (r - l) / 2;
        if (unsigned pairs = checkPairs(mid); pairs >= target) {
            r = mid;
        } else {
            l = ++mid;
        }
    }
    return l;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    array.resize(n);
    for (size_t i = 0; i != n; ++i) {
        std::cin >> array[i];
    }
    std::cin >> k;

    std::sort(array.begin(), array.end());

    std::cout << binSearch(k) << '\n';

    return 0;
}