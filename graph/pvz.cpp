#include <iostream>
#include <vector>
#include <algorithm>

int n;
long long result = 1e18;
int middle;
std::vector<long long> weights;
std::vector<std::vector<int>> graph;
std::vector<long long> subtree;
long long total_sum;

void firstPass(int u, int parent) {
    subtree[u] = weights[u];
    for (int v : graph[u]) {
        if (v == parent) continue;
        firstPass(v, u);
        subtree[u] += subtree[v];
    }
}

void secondPass(int u, int parent) {
    long long max_queue = 0;
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        max_queue = std::max(max_queue, subtree[v]);
    }
    
    if (parent != -1) {
        long long parent_component = total_sum - subtree[u];
        max_queue = std::max(max_queue, parent_component);
    }
    
    if (max_queue < result) {
        result = max_queue;
        middle = u;
    }
    
    for (int v : graph[u]) {
        if (v == parent) continue;
        secondPass(v, u);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cin >> n;
    weights.resize(n + 1);
    graph.resize(n + 1);
    subtree.resize(n + 1);
    
    for (int i = 1; i <= n; i++) {
        std::cin >> weights[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    firstPass(1, -1);
    total_sum = subtree[1];
    
    secondPass(1, -1);
    
    std::cout << middle << '\n';
    return 0;
}