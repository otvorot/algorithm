#include <iostream>
#include <vector>
#include <deque>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);


    int vs;
    std::cin >> vs;
    std::vector<std::vector<int>> graph(vs + 1);
    std::vector<int> depth(vs + 1, -1);
    std::vector<int> parent(vs + 1);
    std::deque<int> queue;


    for (int i = 1; i < vs; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }


    for (int i = 1; i <= vs; ++i) {
        if (graph[i].size() == 1) {
            queue.push_back(i);
            depth[i] = 0;
            parent[i] = i;
        }
    }

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();

        for (int v : graph[u]) {
            if (depth[v] == -1) {
                queue.push_back(v);
                depth[v] = depth[u] + 1;
                parent[v] = parent[u];
            } else {
                if (parent[u] != parent[v]) {
                    std::cout << depth[u] + depth[v] + 1 << '\n';
                    return 0;
                }
            }
        }
    }
}