#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Event {
    short time;
    short office;
    bool start;

    Event(short t, short o, bool s) : time(t), office(o), start(s) {};

    bool operator < (const Event& other) const {
        if (time == other.time) {
            return start < other.start;
        }
        return time < other.time;
    }
};

std::pair<short, short> parser(const std::string& input) {
    std::pair<short, short> result;
    
    result.first = std::stoi(input.substr(0, 2)) * 60 + std::stoi(input.substr(3, 2));
    result.second = std::stoi(input.substr(6, 2)) * 60 + std::stoi(input.substr(9, 2));

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n;

    std::vector<Event> timeline;
    timeline.reserve(n * 2);

    //                                 цикл для первого офиса
    std::string token;
    for (int i = 0; i < n; ++i) {
        std::cin >> token;
        auto [start, finish] = parser(token);
        timeline.emplace_back(Event(start, 0, 1));
        timeline.emplace_back(Event(finish, 0, 0));
    }

    //                               цикл для второго офиса
    std::cin >> m;
    timeline.reserve(2 * (n + m));
    for (int i = 0; i < m; ++i) {
        std::cin >> token;
        auto [start, finish] = parser(token);
        timeline.emplace_back(Event(start, 1, 1));
        timeline.emplace_back(Event(finish, 1, 0));
    }

    std::sort(timeline.begin(), timeline.end());

    int freeBus[2] {0};
    int totalBus[2] {0};
    for (int i = 0; i < timeline.size(); ++i) {
        short& time = timeline[i].time;
        short& office = timeline[i].office;
        bool& start = timeline[i].start;

        if (start) {
            if (freeBus[office]) {
                --freeBus[office];
            } else {
                ++totalBus[office];
            }
        } else {
            ++freeBus[(office + 1) % 2];
        }
    }

    std::cout << totalBus[0] + totalBus[1] << '\n';
}