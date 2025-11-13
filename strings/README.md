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


<details>
<summary>случай верблюда</summary>

## условие
В некоторых IDE поддерживается навигация по файлам через их сокращённые названия. Если в языке принято называть классы CamelCase'ом (как в Java, например), то по заглавным буквам названия можно быстро найти нужный класс. Например, если название класса «***MyFavouriteConfigurableScannerFactory***», то его можно найти по строке «***MFCSF***». Но если в проекте есть класс «***theMultiFunctionalCommaSeparatedFile***», то он тоже будет подходить под этот паттерн, и при поиске надо будет выбрать между этими двумя вариантами.

Вам дан набор строк в CamelCase. Далее будут поступать запросы в виде строк-паттернов из прописных букв английского алфавита. Вам надо находить такие строки среди исходных, которые удовлетворяют заданному шаблону, и выводить их в лексикографическом порядке.

Также в паттерне может быть только несколько первых заглавных букв. Например, если бы в указанном выше примере был бы паттерн «***MFCS***», то существующие две строки походили бы под него, а также подходил бы, например, «***MamaFicusCodingSouthWestNorth***». А вот «***MamaCodingSouthWestNorth***» –— уже нет.

Формат ввода:

В первой строке записано число — количество названий классов в исходном наборе ***n*** (***1 ≤ n ≤ 10⁵***). Все названия состоят из строчных и прописных букв английского алфавита.

В следующих ***n*** строках даны сами названия по одному в строке. Суммарная длина этих строк не превосходит ***10⁷***.

Затем дано количество запросов ***m*** (***1 ≤ m ≤ 100***).

В следующих ***m*** строках даны сами запросы. Каждый запрос –— это шаблон, строка из прописных букв английского алфавита, в длину не превышающая ***10⁵***. Шаблон может быть пустым. Заметьте: шаблону из нуля прописных букв удовлетворяет любое название.

Формат вывода:

Для каждого отдельного запроса (в порядке их поступления) выведите в лексикографическом порядке все строки, которые подходят под данный шаблон. Если какие-то строки одинаковые, то выведите все экземпляры. Если ни одна из строк не подходит под шаблон, то выведите для данного запроса пустую строку.


## идея решения
В узлах префиксного дерева хранятся только заглавные буквы
Каждый узел содержит индексы всех строк, чья последовательность заглавных букв проходит через этот узел
В каждый узел добавляется индекс исходной строки
Поиск идет только по заглавным буквам паттерна
Возвращаются все строки, у которых последовательность заглавных букв начинается с паттерна

Сложность:
Построение: O(L) где L - суммарная длина строк

Поиск: O(k) где k - длина паттерна

Память: O(L) для хранения Trie


```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

class Trie {
    unordered_map<char, Trie*> childs;
    vector<int> ids;
    
public:
    vector<int>& getIds() { return ids; }
    
    void add(const string& word, int id) {
        Trie* node = this;
        for (char c : word) {
            if (isupper(c)) {
                if (!node->childs[c]) node->childs[c] = new Trie();
                node->childs[c]->ids.push_back(id);
                node = node->childs[c];
            }
        }
    }
    
    vector<int> get(const string& word) {
        Trie* node = this;
        for (char c : word) {
            if (!node->childs[c]) return {};
            node = node->childs[c];
        }
        return node->ids;
    }
    
    ~Trie() {
        for (auto& [c, ptr] : childs) delete ptr;
    }
};

int main() {
    int n, m;
    cin >> n; cin.ignore();
    
    vector<string> arr(n);
    Trie trie;
    
    for (int i = 0; i < n; i++) {
        getline(cin, arr[i]);
        trie.getIds().push_back(i);
    }
    
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) trie.add(arr[i], i);
    
    cin >> m; cin.ignore();
    while (m--) {
        string query;
        getline(cin, query);
        for (int id : trie.get(query)) cout << arr[id] << endl;
    }
}
```

</details>


<details>
<summary>packed prefix</summary>

## условие
Вам даны строки в запакованном виде. Определим запакованную строку (ЗС) рекурсивно:

- Строка, состоящая только из строчных букв английского алфавита является ЗС
- Если ***A*** и ***B*** — корректные ЗС, то и ***AB*** является ЗС
- Если ***A*** — ЗС, а ***n*** — однозначное натуральное число, то ***n[A]*** тоже ЗС

При этом запись ***n[A]*** означает, что при распаковке строка ***A*** записывается подряд ***n*** раз.

Найдите наибольший общий префикс распакованных строк и выведите его (в распакованном виде).

Формат ввода:

В первой строке записано число ***n*** (***1 ≤ n ≤ 1000***) – число строк.

Далее в ***n*** строках записаны запакованные строки. Гарантируется, что эти строки корректны, то есть удовлетворяют указанному рекурсивному определению. Длина строк после распаковки не превосходит ***10⁵***.

Формат вывода:

Выведите наибольший общий префикс распакованных строк.

Пример 1
Ввод:
3
2[a]2[ab]
3[a]2[r2[t]]
a2[aa3[b]]

Вывод:
aaa


Пример 2
Ввод:
3
abacabaca
2[abac]a
3[aba]

Вывод:
aba


## идея решения
1. Распаковка строки
Используем два стека: для строк и множителей

Обрабатываем строку посимвольно:
Цифры → сохраняются в стек множителей

'[' → начинает новую подстроку
']' → извлекает подстроку и множитель, умножает, добавляет к предыдущей строке

Буквы → добавляются в текущую строку

2. Поиск общего префикса
Сравниваем две распакованные строки поэлементно
Находим длину общего префикса как min(l1, l2)
Возвращаем общий префикс и его длину


Распаковываем только до момента расхождения префиксов
Не храним все полностью распакованные строки

Сложность:

Распаковка: O(L) где L - длина запакованной строки

Сравнение: O(min(L1, L2)) для каждой пары строк

Память: O(max_распакованная_длина)



```cpp
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>

using namespace std;

pair<vector<char>, int> unpack(const string& str) {
    stack<vector<char>> s_stack;
    stack<int> m_stack;
    s_stack.push(vector<char>());
    
    for (char c : str) {
        if (isdigit(c)) {
            m_stack.push(c - '0');
        } else if (c == '[') {
            s_stack.push(vector<char>());
        } else if (c == ']') {
            vector<char> last = s_stack.top();
            s_stack.pop();
            int multiplier = m_stack.top();
            m_stack.pop();
            
            vector<char> expanded;
            for (int i = 0; i < multiplier; i++) {
                expanded.insert(expanded.end(), last.begin(), last.end());
            }
            
            vector<char> top = s_stack.top();
            s_stack.pop();
            top.insert(top.end(), expanded.begin(), expanded.end());
            s_stack.push(top);
        } else {
            s_stack.top().push_back(c);
        }
    }
    
    vector<char> result = s_stack.top();
    return make_pair(result, result.size());
}

pair<vector<char>, int> find_common_prefix(const vector<char>& seq1, int l1, 
                                         const vector<char>& seq2, int l2) {
    int min_len = min(l1, l2);
    int i = 0;
    
    while (i < min_len && seq1[i] == seq2[i]) {
        i++;
    }
    
    vector<char> common_prefix(seq1.begin(), seq1.begin() + i);
    return make_pair(common_prefix, i);
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    string input;
    getline(cin, input);
    
    auto main_unpacked = unpack(input);
    vector<char> main_seq = main_unpacked.first;
    int len_main_seq = main_unpacked.second;
    
    for (int i = 0; i < n - 1; i++) {
        getline(cin, input);
        auto current_unpacked = unpack(input);
        auto result = find_common_prefix(main_seq, len_main_seq, 
                                       current_unpacked.first, current_unpacked.second);
        main_seq = result.first;
        len_main_seq = result.second;
    }
    
    for (char c : main_seq) {
        cout << c;
    }
    cout << endl;
    
    return 0;
}
```

</details>