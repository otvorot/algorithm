#include <iostream>
#include <vector>

long result = 0;


long dfs(int u, std::vector<std::vector<int>>& tree, std::vector<long>& weights) {
    if (tree[u].empty()) {
        result += std::abs(weights[u]);
        return -weights[u];
    }

    long sendBack = 0;

    for (auto child : tree[u]) {
        sendBack += dfs(child, tree, weights);
    }

    weights[u] += sendBack;
    result += std::abs(weights[u]);

    return sendBack + -weights[u];
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> tree(n);
    std::vector<long> weights(n);

    int token;
    for (int i = 1; i < n; ++i) {
        std::cin >> token;
        tree[token].emplace_back(i);
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }

    long pass = dfs(0, tree, weights);

    std::cout << result << '\n';
}