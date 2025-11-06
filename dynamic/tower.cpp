#include <iostream>
#include <vector>
#include <deque>


short n, k;
std::vector<int> arr;
std::vector<int> dp;
std::vector<short> prev;
std::deque<short> slidingWindow;
int slidingSum = 0;


void addToSliding(short idin) {
    if (!slidingWindow.empty() && slidingWindow.front() <= idin - k) {
        slidingWindow.pop_front();
    }

    while (!slidingWindow.empty() && arr[slidingWindow.back()] > arr[idin]) {
        slidingWindow.pop_back();
    }

    slidingWindow.push_back(idin);
}


int main() {
    std::cin >> n >> k;
    arr.resize(n);
    dp.resize(n - k + 1);
    prev.resize(dp.size(), -1);
    int token;
    short i = 0, j = 0;
    while (j < n) {
        while (j - i < k) {
            std::cin >> token;
            arr[j] = token;           // записал в исходный массив
            addToSliding(j);     // записать в окно
            slidingSum += token;
            ++j;
        }

        dp[i] = slidingSum * arr[slidingWindow.front()];  // получили значение в башне

        if (i - k >= 0) {
            int prevVal = dp[i];
            short prevId;
            for (short l = i - k; l > i - (2 * k); --l) {
                if (l < 0) {
                    break;
                }
                if (dp[l] + dp[i] > prevVal) {
                    prevVal = dp[l] + dp[i];
                    prevId = l;
                }
            }
            dp[i] = prevVal;
            prev[i] = prevId;
        }
        
    
        slidingSum -= arr[i++];
    }
    // std::cout << "1" << std::endl;
    std::vector<short> result;

    token = 0;
    short bestId;
    for (short l = dp.size() - 1; l >= dp.size() - k; --l) {
        if (l < 0) break;
        if (dp[l] > token) {
            token = dp[l];
            bestId = l;
        }
    }

    // std::cout << "2" << std::endl;

    while (bestId != -1) {
        result.push_back(bestId);
        bestId = prev[bestId];
    }

    // std::cout << "3" << std::endl;
    std::cout << result.size() << '\n';
    for (auto x = result.rbegin(); x != result.rend(); ++x) {
        std::cout << *x + 1 << ' ';
    }
    std::cout << "\n";
}