#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


struct Point {
    int name;
    double x;
    double y;
    double vx;
    double vy;

    Point(int a, double b, double c, double d, double(e)) : name(a), x(b), y(c), vx(d), vy(e) {}

    double timeFinish(double L) {
        if (vx <= 0) return -1;
        return (L - x) / vx;
    }

    double timeSide(double W) {
        if (!vy) {
            return 0;
        } else if (vy < 0) {
            return y / -vy;
        } else {
            return (W - y) / vy;
        }
    }

    double timeCollision(const Point& other) {
        
        double dx = other.x - x;
        double dy = other.y - y;
        double dvx = vx - other.vx;
        double dvy = vy - other.vy;

        double tx = dvx ? dx / dvx : 0;
        double ty = dvy ? dy / dvy : 0;

        if (tx > 0 && ty > 0 && tx == ty) return tx;

        if (tx < 0 || ty < 0) return 0;

        double t = std::max(tx, ty);
        if (x + vx * t == other.x + other.vx * t && y + vy * t == other.y + other.vy * t) {
            return t;
        }

        return 0;
    }
};

struct Event {
    int name;
    double time;
    short type;
    int other;

    Event(int n, double t, short ty, int o) : name(n), time(t), type(ty), other(o) {}
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(10);

    int n;
    double L, W;
    std::cin >> n >> L >> W;
    
    std::vector<Point> points;
    std::vector<Event> events;
    events.reserve(n * 2);
    points.reserve(n);

    double a, b, c, d;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a >> b >> c >> d;
        points.emplace_back(Point(i, a, b, c, d));
    }

    for (int i = 0; i < n; ++i) {
        if (double time = points[i].timeFinish(L); time > 0) {
            events.emplace_back(Event(points[i].name, time, 2, 0));
        }

        if (double time = points[i].timeSide(W); time) {
            events.emplace_back(Event(points[i].name, time, 1, 0));
        }

        for (int j = i + 1; j < n; ++j) {
            if (double time = points[i].timeCollision(points[j]); time) {
                events.emplace_back(Event(points[i].name, time, 0, points[j].name));
                events.emplace_back(Event(points[j].name, time, 0, points[i].name));
            }
        }
    }

    std::sort(
        events.begin(),
        events.end(),
        [] (const Event& lhs, const Event& rhs) {
            if (lhs.time == rhs.time) {
                return lhs.type < rhs.type;
            }
            return lhs.time < rhs.time;
        }
    );

    std::vector<double> outsiders(n + 1, false);
    std::vector<int> winners;
    winners.reserve(n);
    for (int i = 0; i < events.size(); ++i) {
        const double& time = events[i].time;
        const int& me = events[i].name;

        if (outsiders[me]) continue;
        const int& other = events[i].other;
        const short& type = events[i].type;
        if (!type) {
            if (!outsiders[other] || outsiders[other] == time) {
                outsiders[me] = time;
            }
        }

        if (type == 1) outsiders[me] = time;

        if (type == 2) {
            int j = i;
            while (j < events.size() && events[j].time == time) {
                if (events[j].type == 2 && !outsiders[events[j].name]) {
                    winners.emplace_back(events[j].name);
                }
                ++j;
            }
            break;
        }
    }

    std::sort(winners.begin(), winners.end());

    std::cout << winners.size() << '\n';
    for (auto& x : winners) {
        std::cout << x << ' ';
    }

    // for (auto& x : events) {
    //     std::cout << x.time << ' ' << x.name << ' ' << x.type << ' ' << x.other << '\n';
    // }
}