#include <iostream>
#include <vector>


class Node {
public:
    std::vector<int> childs;
    int inTime;
    int outTime;

    Node() = default;
    
    void add(int child) {
        childs.emplace_back(child);
    }

    bool predok(const Node& other) {
        return inTime < other.inTime && other.outTime < outTime;
    }
};


void dfs(std::vector<Node>& tree, int root) {
    int counter = 0;
    std::vector<bool> colors(tree.size());
    std::vector<int> stack {root};

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();

        if(!colors[u]) {
            colors[u] = true;
            stack.emplace_back(u);
            tree[u].inTime = counter;

            for (int v : tree[u].childs) {
                if (!colors[v]) {
                    stack.emplace_back(v);
                }
            }


        } else {
            tree[u].outTime = counter;
        }

        ++counter;
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;

    std::cin >> n;

    std::vector<Node> tree(n + 1);
    int root;

    int token;
    for (int i = 1; i <= n; ++i) {
        std::cin >> token;
        tree[token].add(i);
        if (token == 0) {
            root = i;
        }
    }

    dfs(tree, root);

    std::cin >> m;

    while (m) {
        --m;
        int predok, child;
        std::cin >> predok >> child;
        std::cout << tree[predok].predok(tree[child]) << '\n';
    }
    
}