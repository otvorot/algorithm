#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Interval {
public:
    double begin = 0;
    double end = 0;
    double weight = 0;

    Interval(double b, double e, double w) : begin(b), end(e), weight(w) {}
    Interval() = default;

    bool operator < (const Interval& other) {
        return end < other.end;
    }

    bool operator > (const Interval& other) {
        return end > other.end;
    }

    bool operator == (const Interval& other) {
        return end == other.end;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::vector<Interval> intervals;
    std::vector<double> dp;

    std::cin >> n;
    intervals.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        double b, e, w;
        std::cin >> b >> e >> w;
        intervals[i] = Interval(b, e, w);
    }
    std::sort(intervals.begin() + 1, intervals.end());

    for (int i = 1; i <= n; ++i) {
        auto it = std::upper_bound(
            intervals.begin(),
            intervals.begin() + i + 1,
            intervals[i].begin,
            [] (const double& target, const Interval& other) {
                return target < other.end;
            }
        );
        --it;
        dp[i] = std::max(intervals[i].weight + dp[it - intervals.begin()], dp[i - 1]);
    }

    std::cout << std::setprecision(6) << dp.back() << '\n';
}