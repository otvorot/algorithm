#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nTrain, mCar, point;
    std::cin >> nTrain >> mCar >> point;

    std::vector<std::pair<double, double>> occupied;
    occupied.reserve(nTrain);

    for (int i = 0; i < nTrain; ++i) {
        double x, y, v;
        std::cin >> x >> y >> v;
        
        double t1, t2;
        if (x < y) {
            t1 = (point - y) / v;
            t2 = (point - x) / v;
        } else {
            t1 = (y - point) / v;
            t2 = (x - point) / v;
        }
        
        if (t2 < 0) continue;
        
        if (t1 < 0) t1 = 0;
        
        occupied.emplace_back(t1, t2);
    }

    std::sort(occupied.begin(), occupied.end());

    std::vector<std::pair<double, double>> merged;
    for (const auto& interval : occupied) {
        if (merged.empty() || merged.back().second < interval.first) {
            merged.push_back(interval);
        } else {
            merged.back().second = std::max(merged.back().second, interval.second);
        }
    }

    double checkTime;
    std::cout << std::fixed << std::setprecision(10);
    for (int i = 0; i < mCar; ++i) {
        std::cin >> checkTime;
        
        auto it = std::upper_bound(
            merged.begin(), merged.end(), checkTime,
            [](double t, const std::pair<double, double>& interval) {
                return t < interval.first;
            }
        );
        
        if (it == merged.begin()) {
            std::cout << checkTime << '\n';
        } else {
            --it;
            if (checkTime <= it->second) {
                std::cout << it->second << '\n';
            } else {
                std::cout << checkTime << '\n';
            }
        }
    }

    return 0;
}