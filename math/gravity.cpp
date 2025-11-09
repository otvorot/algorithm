#include <iostream>
#include <vector>
#include <algorithm>

long weightsum(
    std::vector<long long>& a,
    std::vector<long long>& b,
    std::vector<long long>& sorted,
    std::vector<long long>& prefix
) {
    long long sum = 0;
    for (int i = 0; i < a.size(); ++i) {
        long long ai = a[i];
        int pos = std::upper_bound(sorted.begin(), sorted.end(), ai) - sorted.begin();
        long long left = pos * ai - prefix[pos];
        long long right = prefix.back() - prefix[pos] - ai * (sorted.size() - pos);
        sum += i * (left + right);
    }

    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<long long> a;
    std::vector<long long> b;
    std::vector<long long> sorted;
    std::vector<long long> prefix;

    int n;
    std::cin >> n;
    a.resize(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int m;
    std::cin >> m;
    sorted.resize(m);
    prefix.resize(m + 1);
    b.resize(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
        sorted[i] = b[i];
    }

    std::sort(sorted.begin(), sorted.end());

    for (int i = 1; i < prefix.size(); ++i) {
        prefix[i] = prefix[i - 1] + sorted[i - 1];
    }

    long long left = weightsum(a, b, sorted, prefix);

    sorted = a;
    std::sort(sorted.begin(), sorted.end());
    prefix.resize(n + 1);
    for (int i = 1; i < prefix.size(); ++i) {
        prefix[i] = prefix[i - 1] + sorted[i - 1];
    }

    long long right = weightsum(b, a, sorted, prefix);

    std::cout << left - right << '\n';
}