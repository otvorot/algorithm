#include <iostream>
#include <vector>
#include <deque>


int n;
std::vector<int> a, b;

bool check(int k) {
    std::deque<std::pair<int, int>> q;
    int j = 0;

    for (int i = 0; i < n; i++) {
        while (j < a.size() && j <= i + k) {
            q.push_back({j, a[j]});
            ++j;
        }
        
        int cap = b[i];
        
        while (cap > 0 && !q.empty()) {
            std::pair<int, int>& front = q.front();
            if (front.first + k < i) return false;
            int take = std::min(cap, front.second);
            cap -= take;
            front.second -= take;
            if (front.second == 0) q.pop_front();
        }
    }
    return q.empty();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    a.resize(n);
    b.resize(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    int l = 0, r = n;
    bool flag;
    while (l < r) {
        int mid = l + (r - l) / 2;
        flag = check(mid);

        if (flag) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    std::cout << (l != n ? l : -1) << '\n'; 
}