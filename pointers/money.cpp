#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Tablichka {
    long double value = 0;
    int id = 0;

    Tablichka() = default;
    Tablichka(long double v, int i) : value(v), id(i) {}

    bool operator < (const Tablichka& other) const {
        return value < other.value;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    long double target;
    std::cin >> n >> target;
    std::vector<Tablichka> array(n);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i].value;
        array[i].id = i + 1;
    }
    
    std::sort(array.begin(), array.end());
    
    long double delta = std::numeric_limits<double>::max();
    int delimoeBest, delitelBest;
    
    auto delimoe = array.end() - 1;
    while (delimoe != array.begin()) {
        long double delitelPredicted = delimoe->value / target;
        auto delitelInArray = std::upper_bound(array.begin(), delimoe, Tablichka(delitelPredicted, 0));

        if (delitelInArray != delimoe) {
            if (long double newDelta = std::abs(delimoe->value / delitelInArray->value - target); newDelta < delta) {
                delta = newDelta;
                delimoeBest = delimoe->id;
                delitelBest = delitelInArray->id;
            }
        }

        --delitelInArray;
        
        if (delitelInArray >= array.begin()) {
            if (long double newDelta = std::abs(delimoe->value / delitelInArray->value - target); newDelta < delta) {
                delta = newDelta;
                delimoeBest = delimoe->id;
                delitelBest = delitelInArray->id;
            }
        }

        --delimoe;
    }
    
    std::cout << delimoeBest << " " << delitelBest << '\n';
}