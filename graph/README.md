# задачи на графы



<details>
<summary>из тупика в тупик</summary>

## условие
Каждый вечер после работы Вася приходит домой и думает о жизни. Вася описал свои перспективы в виде ***n*** жизненных ситуаций и соединил их ***n−1*** двунаправленными переходами так, что между двумя любыми жизненными ситуациями существовал ровно один простой путь, возможно через промежуточные ситуации. ***Жизненным тупиком*** называется жизненная ситуация, из которой существует ровно один переход.

Помогите Васе найти самый короткий путь из одного жизненного тупика в другой.

Формат ввода
В первой строке вводится целое число ***n*** — число жизненных ситуаций (***2 ≤ n ≤ 10^5***).
В следующих ***n−1*** строках заданы по два числа ***a_i***, ***b_i*** — номера жизненных ситуаций, между которыми возможен переход (***1 ≤ a_i, b_i ≤ n***).
Гарантируется, что между любыми двумя жизненными ситуациями существует ровно один простой путь.

Формат вывода
Выведите одно число — минимальное количество переходов, которое нужно совершить Васе чтобы попасть из одного жизненного тупика в другой.

## идея решения
запускаем поиск в ширину одновременно из всех листьев дерева и отмечаем глубину каждого узла. при встрече двух треков складываем их глубины + 1. временная сложность O(n), пространственная O(n)

```cpp
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
```

</details>


<details>
<summary>феодальная реформа</summary>

## условие
Феодальное государство представляет собой подвешенное дерево из ***n*** вершин, являющихся городами. Вершина ***0*** — это столица, а для любого другого города известен город, которому он непосредственно подчиняется.

В этом государстве широко распространены трансферы из феодального бюджета — некоторые города могут получать дотации, а другие — платить дополнительные налоги. Для каждого города ***i*** известен баланс с феодальным бюджетом ***a_i***, который может быть как положительным, так и отрицательным.

Было решено покончить с этой практикой, но напрямую изменять налоги или дотации в отдельных городах нельзя — из-за феодальной иерархии: *«вассал моего вассала — не мой вассал»*.

Однако можно издавать **эдикты**. Каждый эдикт действует на **весь путь от столицы (вершины ***0***) до выбранной вершины ***v***. При этом баланс во всех вершинах на этом пути изменяется на ***+1*** или ***−1***.

Таким образом, за одно действие можно выбрать любую вершину ***v*** и изменить на ***1*** значения ***a_i*** для всех вершин ***i***, лежащих на пути от ***0*** до ***v***.

Цель реформы — сделать баланс во всех городах равным ***0***, используя **наименьшее возможное количество эдиктов**.

Формат ввода

- В первой строке дано целое число ***n*** — количество вершин в дереве (***1 ≤ n ≤ 100 000***).
- В следующих ***n − 1*** строках даны целые числа ***p_i*** — номер предка вершины ***i*** (***0 ≤ p_i < n***, ***1 ≤ i < n***). Гарантируется, что дано подвешенное дерево с корнем в вершине ***0***.
- В последней строке даны ***n*** целых чисел — исходные значения в вершинах (***|a_i| ≤ 100 000***).

Формат вывода

Выведите единственное число — **минимальное количество эдиктов**, необходимых для проведения реформы.


## идея решения
Задача сводится к обходу дерева снизу вверх (DFS), где для каждой вершины мы:
- Учитываем, сколько изменений пришло от потомков («накопленный поток»),
- Корректируем текущее значение баланса,
- Определяем, сколько новых эдиктов нужно начать или завершить в этой вершине.

Ключевая идея: **каждый эдикт — это прибавление или вычитание 1 на пути от корня до листа**. Мы можем представить, что «поток» изменений идёт от корня вниз. Если в поддереве нужно скомпенсировать избыток или недостаток, мы «запускаем» нужное количество таких потоков.

Время: O(n) — каждый узел посещается один раз.
Память: O(n) — хранение дерева и весов.


```cpp
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
```

</details>


<details>
<summary>предок</summary>

## условие
Напишите программу, которая для двух вершин дерева определяет, является ли одна из них **предком** другой.

Формат ввода

- В первой строке дано натуральное число ***n*** — количество вершин в дереве (***1 ≤ n ≤ 100 000***).
- Во второй строке находятся ***n*** чисел: ***i***-е число указывает номер **непосредственного родителя** вершины с номером ***i***.  
  Если значение равно ***0***, то вершина ***i*** является **корнем** дерева.
- В третьей строке дано число ***m*** — количество запросов (***1 ≤ m ≤ 100 000***).
- Каждая из следующих ***m*** строк содержит два различных числа ***a*** и ***b*** (***1 ≤ a, b ≤ n***).

> ⚠️ Вершины нумеруются с **1**.

Формат вывода

Для каждого из ***m*** запросов выведите:
- ***1***, если вершина ***a*** является **одним из предков** вершины ***b*** (то есть ***a*** лежит на пути от корня до ***b***),
- ***0*** в противном случае.

Каждый ответ выводится на отдельной строке.


## идея решения
стандартная задача, за один обход в глубину отмечаем время входа - выхода вершины. определить является ли ***u*** предком ***v*** можно за O(1) проверив ***время входа u < время входа v*** и ***время выхода v < время выхода u***.
временная сложность O(n + m), где m - к-во запросов
пространственная O(n)


```cpp
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
```

</details>


<details>
<summary>пункт выдачи</summary>

## условие
Город **Деревянск** состоит из ***n*** площадей, соединённых двусторонними дорогами. Дороги устроены так, что **между любыми двумя площадями существует единственный путь** — то есть структура города представляет собой **дерево**.

На ***i***-й площади живёт ***a_i*** человек.

Планируется открыть **пункт выдачи заказов** на одной из площадей. Все жители города придут за своими заказами в первый день.

Как организованы входы:
- **Один вход** — для жителей **той площади, где находится пункт выдачи**.
- **По одному входу** — с каждой стороны дороги, ведущей к соседней площади.
- Каждый вход обслуживает **всех жителей, которые "идут через этот вход"**, то есть живут в той части города, которая доступна только через эту дорогу.

Очереди:
- Перед каждым входом выстраивается очередь из всех жителей, приходящих через него.
- Цель — **минимизировать длину самой большой очереди**.

Задача

Выбрать номер площади для пункта выдачи так, чтобы **максимальная длина очереди** (среди всех входов) была **наименьшей возможной**.

Если таких площадей несколько — вывести **любую**.

---

Формат ввода

- Первая строка: целое число ***n*** — количество площадей (***1 ≤ n ≤ 100 000***).
- Вторая строка: ***n*** целых чисел ***a_i*** — количество жителей на каждой площади (***1 ≤ a_i ≤ 10⁹***).
- Следующие ***n−1*** строк: пары чисел ***v_j, u_j*** — номера площадей, соединённых дорогой (***1 ≤ v_j, u_j ≤ n***).

Гарантируется, что граф — **связное дерево**.

---

Формат вывода

Выведите одно число — **номер площади**, на которой следует открыть пункт выдачи. Если возможных ответов несколько, выведите **любой из оптимальных**.


## идея решения
задача решается за  линейное время, двумя обходами в глубину. в первом проходе мы считаем для кадого узла суммарный вес его детей (поддеревьев). на втором проходе мы выбираем минимум из поддеревьев детей и родительской компоненты. ее вычисляем - общий вес всего графа минус вес текущего поддерева.


```cpp
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
```

</details>


<details>
<summary>топологическая сортировка</summary>

## условие
Дан ациклический ориентированный граф (так называемый ***DAG***, directed acyclic graph). Найдите его топологическую сортировку, то есть выведите его вершины в таком порядке, что все рёбра графа идут слева направо. У графа может быть несколько подходящих перестановок вершин. Вам надо найти любую топологическую сортировку.

Формат ввода:

В первой строке даны два числа – количество вершин ***n*** (***1 ≤ n ≤ 10⁵***) и количество рёбер ***m*** (***0 ≤ m ≤ 10⁵***). В каждой из следующих ***m*** строк описаны рёбра по одному на строке. Каждое ребро представлено парой вершин ***(from, to)***, ***1 ≤ from, to ≤ n***, соответственно номерами вершин начала и конца.

Формат вывода:

Выведите номера вершин в требуемом порядке.


```py
class Vertex:
    def __init__(self, v):
        self.v = v
        self.heap = [0]
        self.last = 0
    def push(self, w):
        self.last += 1
        self.heap.append(w)
        self.sift_up(self.last)
    def sift_up(self, last):
        if last == 1:
            return
        parent = last // 2
        if self.heap[last] < self.heap[parent]:
            self.heap[last], self.heap[parent] = self.heap[parent], self.heap[last]
            self.sift_up(parent)
    def pull(self):
        if self.last == 0:
            return None
        self.heap[1], self.heap[self.last] = self.heap[self.last], self.heap[1]
        back = self.heap.pop()
        self.last -= 1
        self.sift_down(1, self.last)
        return back
    def sift_down(self, first, last):
        left, right = first * 2, first * 2 + 1
        if left > last:
            return
        smallest = right if right <= last and self.heap[right] < self.heap[left] else left
        if self.heap[first] < self.heap[smallest]:
            return
        self.heap[first], self.heap[smallest] = self.heap[smallest], self.heap[first]
        self.sift_down(smallest, last)

def trvrse(v, colors, vertice, prima):
    stack = []
    stack.append(v)
    while stack:
        now = stack.pop()
        if not colors[now.v]:
            colors[now.v] = 1
            stack.append(now)
            next = now.pull()
            while next:
                if not colors[next]:
                    stack.append(vertice[next])
                next = now.pull()
        elif colors[now.v] == 1:
            colors[now.v] = 2
            prima.append(now.v)
            

def main():
    vs, es = map(int, input().split())
    colors = [0] * (vs + 1)
    vertice = [0] * (vs + 1)
    prima = []
    for _ in range(es):
        v, w = map(int, input().split())
        if not vertice[v]:
            vertice[v] = Vertex(v)
        if not vertice[w]:
            vertice[w] = Vertex(w)
        vertice[v].push(w)
    for i in range(1, vs + 1):
        if not colors[i] and not vertice[i]:
            prima.append(i)
            colors[i] = 2
        elif not colors[i] and vertice[i]:
            trvrse(vertice[i], colors, vertice, prima)
    print(*prima[::-1])

if __name__ == '__main__':
    main()
```

</details>