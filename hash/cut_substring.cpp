#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int lenRef, k;
    std::cin >> lenRef >> k;

    std::string reference;
    std::cin >> reference;

    std::unordered_map<std::string, std::vector<int>> mapa;
    mapa.reserve(k);

    std::string input;
    for (int i = 1; i <= k; ++i) {
        std::cin >> input;
        mapa[input].push_back(i);
    }

    int nSyms = lenRef / k;
    int begin = 0;
    while (k > 0) {
        std::string token = reference.substr(begin, nSyms);
        std::cout << mapa[token].back() << ' ';
        mapa[token].pop_back();
        --k;
        begin += nSyms;
    }

}