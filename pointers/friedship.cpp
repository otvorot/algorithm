#include <iostream>
#include <vector>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<long> arr(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }


    int bestl = 0, bestr = n - 1;
    long lSum = arr[0], rSum = arr[n - 1];
    long bestDiff = std::abs(lSum - rSum);

    int l = 0, r = n - 1;
    while (l < r) {
        while (l < r - 1 && lSum < rSum) {
            ++l;
            lSum += arr[l];
        }
        
        if (long newDiff = std::abs(lSum - rSum); newDiff < bestDiff) {
            bestDiff = newDiff;
            bestl = l;
            bestr = r;
        }
        
        if (l != 0) {
            if (long newDiff = std::abs(lSum - arr[l] - rSum); newDiff < bestDiff) {
                bestDiff = newDiff;
                bestl = l - 1;
                bestr = r;
            }
        }

        --r;
        rSum += arr[r];
    }

    std::cout << bestDiff << ' ' << bestl + 1 << ' ' << bestr + 1 << '\n';
}