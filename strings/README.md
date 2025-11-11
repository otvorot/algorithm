# задачки на строки


<details>
<summary>пять подряд</summary>

## условие
На большом игровом поле кто-то играл в крестики-нолики (возможно, не соблюдая правила). Цель игры — выстроить пять одинаковых фигур по горизонтали, вертикали или диагонали. Определите, найдется ли такая пятёрка фигур или нет.

Формат ввода
В первой строке ввода записаны числа n и m (1 ≤ n,m ≤ 1000) — размеры игрового поля.
В следующих n строках записано по m символов ”X”, ”O” или ”.”, которые задают крестик, нолик и пустую клетку, соответственно. ”X” и ”O” — заглавные английские буквы

Формат вывода
Выведите Yes, если найдется пять одинаковых фигур подряд, и No в противном случае.

## идея решения
идея заключается в хранении каждой двух диагоналей, вертикали. строку хранить не будем, но обрабатывать на ходу. каждую диагональ привяжем к позиции *y* в которую она ведёт, некоторые за пределами поля. и в каждом наборе будем поддерживать количество *+* и *-*. так мы сможем решить проблему за линейное время, точнее за O(n*m). затраты на память константны.


```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <array>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<char>> field(n, std::vector<char>(m));
    std::unordered_map<int, std::array<int, 3>> lDiag;
    std::unordered_map<int, std::array<int, 3>> rDiag;
    std::unordered_map<int, std::array<int, 3>> vert;
    std::unordered_map<char, int> keys{
        {'X', 0},
        {'O', 1},
        {'.', 2}
    };

    for (int i = 0; i < n; ++i) {
        std::string input;
        std::cin >> input;
        std::array<int, 3> line = {0}; // Для горизонтальной проверки в текущей строке
        
        for (int j = 0; j < m; ++j) {
            field[i][j] = input[j];

            // Горизонтальная проверка
            if (j >= 5) {
                --line[keys[field[i][j - 5]]];
            }
            ++line[keys[input[j]]];
            if (line[keys[input[j]]] == 5 && input[j] != '.') {
                std::cout << "Yes\n";
                return 0;
            }

            // Вертикальная проверка
            if (i >= 5) {
                --vert[j][keys[field[i - 5][j]]];
            }
            ++vert[j][keys[input[j]]];
            if (vert[j][keys[input[j]]] == 5 && input[j] != '.') {
                std::cout << "Yes\n";
                return 0;
            }

            // Левая диагональ (верхний левый -> нижний правый)
            int lKey = i - j;
            if (i >= 5 && j >= 5) {
                --lDiag[lKey][keys[field[i - 5][j - 5]]];
            }
            ++lDiag[lKey][keys[input[j]]];
            if (lDiag[lKey][keys[input[j]]] == 5 && input[j] != '.') {
                std::cout << "Yes\n";
                return 0;
            }

            // Правая диагональ (верхний правый -> нижний левый)
            int rKey = i + j;
            if (i >= 5 && j + 5 < m) {
                --rDiag[rKey][keys[field[i - 5][j + 5]]];
            }
            ++rDiag[rKey][keys[input[j]]];
            if (rDiag[rKey][keys[input[j]]] == 5 && input[j] != '.') {
                std::cout << "Yes\n";
                return 0;
            }
        }
    }

    std::cout << "No\n";
    return 0;
}
```

</details>


<details>
<summary>разрезаная строка</summary>

## условие
Строка s была разрезана на k частей одинаковой длины. По строке s и перемешанным частям определите, в каком порядке их нужно склеить, чтобы получить строку s.

Формат ввода
В первой строке записано два числа n и m (1 ≤ n,m ≤ 10**6) — длина строки и количество кусков соответственно.

Во второй строке записана строка 
s (1 ≤ ∣s∣ ≤ 10**6) — строка, которую необходимо получить.

В i-й из следующих m строк дана строка t_i — описание i-го куска исходной строки.

Гарантируется, что n делится на m и из данных кусков можно составить исходную строку.

Формат вывода
Выведите m различных целых чисел a_i (1 ≤ a_i ≤m), таких, что если заменить число на i-й позиции куском с номером a_i и склеить получившиеся куски, получится исходная строка.

Если ответов несколько, выведите любой.


## идея решения
входные подстроки складываем в мапу, где ключ подстрока, а значение её порядковый номер. так-как гарантировано строка делиться на k, то по подстроке фиксированой длины извлекаем из мапы значение и выводим. решается за O(n) времени и O(n) памяти


```cpp
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
```

</details>