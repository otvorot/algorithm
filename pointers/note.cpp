#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


bool pomeschaetsa(double k, const std::vector<std::pair<double, double>>& words, double W, double H) {
    double curH = 0.0;
    double curW = 0.0;
    double lineH = 0.0;
    
    for (const auto& word : words) {
        double scaledW = k * word.first;
        double scaledH = k * word.second;

        if (scaledW > W || scaledH > H) {
            return false;
        }
        
        if (curW + scaledW <= W && lineH == scaledH) {
            curW += scaledW;

        } else {
            curH += lineH;
            if (curH + scaledH > H) {
                return false;
            }
            curW = scaledW;
            lineH = scaledH;
        }
    }
    
    curH += lineH;

    return curH <= H;
}

int main() {
    int n;
    double W, H;
    std::cin >> n >> W >> H;
    
    std::vector<std::pair<double, double>> words(n);
    for (int i = 0; i < n; i++) {
        std::cin >> words[i].first >> words[i].second;
    }
    

    double l = 0., r = 1000000000.;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (l + r) / 2.;
        if (pomeschaetsa(mid, words, W, H)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    
    std::cout << std::fixed << std::setprecision(10) << l << '\n';
}