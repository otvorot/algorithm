# структурки


<details>
<summary>фигон</summary>

## условие
Язык «Фигон» поддерживает работу со списками чисел, а также позволяет присваивать отдельные имена частям списка. Вам предстоит реализовать интерпретатор языка «Фигон». Полный перечень операций, поддерживаемый языком «Фигон»:

 - List a = new List(x,y, ...,z). Создать новый список из чисел, перечисленных в скобках и присвоить ему имя a.
 - List b = a.subList(from,to). Взять все числа из списка a, находяшиеся на позициях от from до to (from ≤ to) и составить из них список b. Все изменения списка a отражаются в соответствующих позициях списка b, и наоборот. Обратите внимание на тестовые примеры и комментарии к ним.
 - a.set(i,x) Присвоить i элементу списка a значение x
 - a.add(x) Добавить число x в конец списка a. Эта операция применима только в том случае, если список a был создан так, как описано в первой операции (то есть список a не был создан, как подсписок какого-либо другого списка).
 - a.get(i) Вывести i элемент списка a в отдельной строке


Формат ввода
В первой строке вводится целое число n (1 ≤ n ≤ 100000) — количество строк в программе.

Каждая из следующих n строк описывает очередную команду в формате, описанном выше.

Гарантируется, что никакой список не будет объявлен дважды, все обращения к спискам по индексу не выходят за границы списка.

Все названия списков являются строками из строчных латинских букв длиной не более 10.

Слова «new», «list», «set», «add» и «get» являются зарезервироваными и не могут быть названием списка.

Внутри скобок между аргументами и запятыми пробелов нет.

Все числа во входном файле целые, положительные и не превосходят 10^9.

Суммарная длина списков, созданных с помощью первой операции, не превосходит 100000.

Формат вывода
Для каждой операции a.get(i) выведите i элемент списка a.


## идея решения
особой идеи тут нет, просто аккуратно реализовываем что просят. единственный момент на который нужно обратить внимание это то, что подсписков исходного списка может быть очень много, поэтому избегаем лишнего копирования используя указатели на исходный список.


```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>
#include <array>


struct List {
    std::shared_ptr<std::vector<std::string>> data;
    size_t offset = 0;

    List() : data(std::make_shared<std::vector<std::string>>()) {}

    List(std::shared_ptr<std::vector<std::string>> vector) : data(vector) {}

    List(List& other, size_t off) {
        data = other.data;
        offset = other.offset + off - 1;
    }

    void set(size_t i, std::string& newNum) {
        size_t id = (i - 1) + offset;
        (*data)[id] = newNum;
    }

    void add(std::string& newNum) {
        data->push_back(newNum);
    }

    void get(size_t i) {
        size_t id = (i - 1) + offset;
        std::cout << (*data)[id] << '\n';
    }
};

std::unordered_map<std::string, List> mapa;

std::vector<std::string> split(std::string input, size_t start, size_t end, char sep) {
    std::vector<std::string> output;
    std::string token;
    for (size_t i = start; i <= end; ++i) {
        if (input[i] == sep || i == end) {
            output.push_back(token);
            token = "";
        } else {
            token += input[i];
        }
    }
    return output;
}

void makeNew(std::string& name, std::string& nums) {
    std::vector<std::string> forList = split(nums, 5, nums.size() - 1, ',');
    mapa.emplace(name, List(std::make_shared<std::vector<std::string>>(std::move(forList))));
}

std::vector<std::string> getAction(std::string& action) {
    std::string name;
    std::string comand;
    std::string nums;
    
    size_t i = 0;
    while (action[i] != '.') {
        name += action[i++];
    }
    ++i;
    while (action[i] != '(') {
        comand += action[i++];
    }
    ++i;
    while (action[i] != ')') {
        nums.push_back(action[i++]);
    }
    
    return {name, comand, nums};
}

void makeSub(std::string& nameNew, std::string& nameRef, size_t offset) {
    mapa.emplace(nameNew, List(mapa[nameRef], offset));
}

void parser(std::string& input) {
    std::vector<std::string> tokens = split(input, 0, input.size(), ' ');


    if (tokens.size() == 5) {
        makeNew(tokens[1], tokens[4]);

    } else if (tokens.size() == 4) {
        std::vector<std::string> actionParts = getAction(tokens[3]);
        std::string name = actionParts[0];
        std::string comand = actionParts[1];
        std::string nums = actionParts[2];
        std::vector<std::string> slice = split(nums, 0, nums.size(), ',');
        makeSub(tokens[1], name, std::stoi(slice[0]));

    } else {
        std::vector<std::string> actionParts = getAction(tokens[0]);
        std::string name = actionParts[0];
        std::string comand = actionParts[1];
        std::string nums = actionParts[2];
        if (comand == "get") {
            mapa[name].get(std::stoi(nums));
        } else if (comand == "add") {
            mapa[name].add(nums);
        } else {
            std::vector<std::string> idValue = split(nums, 0, nums.size(), ',');
            mapa[name].set(std::stoi(idValue[0]), idValue[1]);
        }
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();
    mapa.reserve(n);


    std::string input;
    while (std::getline(std::cin, input)) {
        parser(input);
    }
}

```

</details>


<details>
<summary>дек на кольцевом буфере</summary>

## условие
Гоша реализовал структуру данных Дек, максимальный размер которого определяется заданным числом. Методы `push_back(x)`, `push_front(x)`, `pop_back()`, `pop_front()` работали корректно. Но, если в деке было много элементов, программа работала очень долго. Дело в том, что не все операции выполнялись за ***O(1)***. Помогите Гоше! Напишите эффективную реализацию.

**Внимание:** при реализации используйте кольцевой буфер.

Формат ввода:

В первой строке записано количество команд ***n*** — целое число, не превосходящее ***100000***. Во второй строке записано число ***m*** — максимальный размер дека. Он не превосходит ***50000***. В следующих ***n*** строках записана одна из команд:

- `push_back(value)` – добавить элемент в конец дека. Если в деке уже находится максимальное число элементов, вывести «error».
- `push_front(value)` – добавить элемент в начало дека. Если в деке уже находится максимальное число элементов, вывести «error».
- `pop_front()` – вывести первый элемент дека и удалить его. Если дек был пуст, то вывести «error».
- `pop_back()` – вывести последний элемент дека и удалить его. Если дек был пуст, то вывести «error».

***Value*** — целое число, по модулю не превосходящее ***1000***.

Формат вывода:

Выведите результат выполнения каждой команды на отдельной строке. Для успешных запросов `push_back(x)` и `push_front(x)` ничего выводить не надо.



```cpp
#include <iostream>
#include <vector>
#include <string>


class Deque {
private:
    const short LIM = 1111;
    std::vector<short> deque;
    int head = 0, tail = 0;
    size_t capacity;
    
public:
    Deque(size_t m) : capacity(m) {
        deque.resize(m, LIM);
    }
    
    void push_back(const short& value) {
        if (deque[tail] == LIM) {
            deque[tail] = value;
            tail = (tail + 1) % capacity;
        } else {
            std::cout << "error" << '\n';
        }
    }
    
    void push_front(const short& value) {
        int idx = (head - 1 + capacity) % capacity;
        if (deque[idx] == LIM) {
            head = idx;
            deque[head] = value;
        } else {
            std::cout << "error" << '\n';
        }
    }
    
    short pop_back() {
        int idx = (tail - 1 + capacity) % capacity;
        if (deque[idx] != LIM) {
            tail = idx;
            short outp = deque[tail];
            deque[tail] = LIM;
            return outp;
        }

        return 1111;
    }
    
    short pop_front() {
        if (deque[head] != LIM) {
            short outp = deque[head];
            deque[head] = LIM;
            head = (head + 1) % capacity;
            return outp;
        }
        
        return 1111;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    short input, output;
    std::string command;
    std::cin >> n >> m;
    Deque deq(m);
    
    for (int i = 0; i != n; ++i) {
        std::cin >> command;
        
        if (command == "push_back") {
            std::cin >> input;
            deq.push_back(input);
        } else if (command == "push_front") {
            std::cin >> input;
            deq.push_front(input);
        } else if (command == "pop_front") {
            output = deq.pop_front();
            std::cout << (output == 1111 ? "error" : std::to_string(output)) << '\n';
        } else if (command == "pop_back") {
            output = deq.pop_back();
            std::cout << (output == 1111 ? "error" : std::to_string(output)) << '\n';
        }
    }
    
    return 0;
}
```

</details>


<details>
<summary>хеш-мапа</summary>

## условие
Хеш-таблица должна поддерживать следующие операции:

- ***put key value*** — добавление пары ключ-значение. Если заданный ключ уже есть в таблице, то соответствующее ему значение обновляется.
- ***get key*** — получение значения по ключу. Если ключа нет в таблице, то вывести «None». Иначе вывести найденное значение.
- ***delete key*** — удаление ключа из таблицы. Если такого ключа нет, то вывести «None», иначе вывести хранимое по данному ключу значение и удалить ключ.

В таблице хранятся уникальные ключи.

Требования к реализации:

- Нельзя использовать имеющиеся в языках программирования реализации хеш-таблиц
- Разрешать коллизии следует с помощью метода цепочек или с помощью открытой адресации
- Все операции должны выполняться за ***O(1)*** в среднем
- Поддерживать рехеширование и масштабирование хеш-таблицы не требуется
- Ключи и значения — целые числа. Поддерживать произвольные хешируемые типы не требуется

Формат ввода:

В первой строке задано общее число запросов к таблице ***n*** (***1 ≤ n ≤ 10⁶***).

В следующих ***n*** строках записаны запросы, которые бывают трех видов – ***get***, ***put***, ***delete***.

Все ключи и значения — целые числа, не превосходящие ***10⁹*** по модулю. Числа могут быть и отрицательными.

При любой последовательности команд, количество ключей в хеш-таблице не может превышать ***10⁵***.

Формат вывода:

На каждый запрос вида ***get*** и ***delete*** выведите ответ на него в отдельной строке.



```cpp
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class Node {
public:
    int key;
    int value;
    Node* next;
    
    Node(int k, int v, Node* n = nullptr) : key(k), value(v), next(n) {}
};

class SelfMadeHashTable {
private:
    std::vector<Node*> bins;
    static const int POW_BINS = 18;
    static const int TABLE_SIZE = 1 << POW_BINS; // 2^18
    
    size_t get_hash(int key) const {
        const unsigned long long s = 2654435769;
        const unsigned long long mod = 1ULL << 32;
        
        unsigned long long hash_val = ((static_cast<unsigned long long>(key) % mod) * s) % mod;
        return hash_val >> (32 - POW_BINS);
    }

public:
    SelfMadeHashTable() : bins(TABLE_SIZE, nullptr) {}
    
    ~SelfMadeHashTable() {
        for (size_t i = 0; i < bins.size(); ++i) {
            Node* current = bins[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }
    
    void put(int key, int value) {
        size_t hash = get_hash(key);
        
        if (bins[hash] == nullptr) {
            bins[hash] = new Node(key, value);
        } else {
            Node* node = bins[hash];
            bool updated = false;
            
            while (node != nullptr) {
                if (node->key == key) {
                    node->value = value;
                    updated = true;
                    break;
                }
                node = node->next;
            }
            
            if (!updated) {
                bins[hash] = new Node(key, value, bins[hash]);
            }
        }
    }
    
    std::string get(int key) const {
        size_t hash = get_hash(key);
        Node* node = bins[hash];
        
        while (node != nullptr) {
            if (node->key == key) {
                return std::to_string(node->value);
            }
            node = node->next;
        }
        
        return "None";
    }
    
    std::string delete_key(int key) {
        size_t hash = get_hash(key);
        Node* prev = nullptr;
        Node* current = bins[hash];
        
        while (current != nullptr) {
            if (current->key == key) {
                int result = current->value;
                
                if (prev == nullptr) {
                    bins[hash] = current->next;
                } else {
                    prev->next = current->next;
                }
                
                delete current;
                return std::to_string(result);
            }
            
            prev = current;
            current = current->next;
        }
        
        return "None";
    }
};

int main() {
    int n;
    std::cin >> n;
    
    SelfMadeHashTable table;
    
    for (int i = 0; i < n; ++i) {
        std::string command;
        std::cin >> command;
        
        if (command == "put") {
            int key, value;
            std::cin >> key >> value;
            table.put(key, value);
        } else if (command == "get") {
            int key;
            std::cin >> key;
            std::cout << table.get(key) << std::endl;
        } else if (command == "delete") {
            int key;
            std::cin >> key;
            std::cout << table.delete_key(key) << std::endl;
        }
    }
    
    return 0;
}
```

</details>


<details>
<summary>хипсорт</summary>

## условие
Тимофей решил организовать соревнование по спортивному программированию, чтобы найти талантливых стажёров. Задачи подобраны, участники зарегистрированы, тесты написаны. Осталось придумать, как в конце соревнования будет определяться победитель.

Каждый участник имеет уникальный логин. Когда соревнование закончится, к нему будут привязаны два показателя: количество решённых задач ***P_i*** и размер штрафа ***F_i***. Штраф начисляется за неудачные попытки и время, затраченное на задачу.

Тимофей решил сортировать таблицу результатов следующим образом: при сравнении двух участников выше будет идти тот, у которого решено больше задач. При равенстве числа решённых задач первым идёт участник с меньшим штрафом. Если же и штрафы совпадают, то первым будет тот, у которого логин идёт раньше в алфавитном (лексикографическом) порядке.

Тимофей заказал толстовки для победителей и накануне поехал за ними в магазин. В своё отсутствие он поручил вам реализовать алгоритм сортировки кучей (англ. Heapsort) для таблицы результатов.

***В данной задаче необходимо реализовать сортировку кучей. При этом кучу необходимо реализовать самостоятельно, использовать имеющиеся в языке реализации нельзя.***

Формат ввода:

В первой строке задано число участников ***n***, ***1 ≤ n ≤ 100000***.

В каждой из следующих ***n*** строк задана информация про одного из участников.

***i***-й участник описывается тремя параметрами:

- уникальным логином (строкой из маленьких латинских букв длиной не более ***20***)
- числом решённых задач ***P_i***
- штрафом ***F_i***

***F_i*** и ***P_i*** — целые числа, лежащие в диапазоне от ***0*** до ***10⁹***.

Формат вывода:

Для отсортированного списка участников выведите по порядку их логины по одному в строке.


```cpp
#include <iostream>
#include <vector>
#include <string>
#include <utility>

struct Participant {
    int score;
    int penalty;
    std::string name;
    
    Participant(int s, int p, const std::string& n) : score(s), penalty(p), name(n) {}
    
    bool operator<(const Participant& other) const {
        if (score != other.score) {
            return score > other.score;
        }
        return penalty < other.penalty;
    }
};

void sift_up(std::vector<Participant>& heap, int last_idx) {
    if (last_idx == 1) {
        return;
    }
    int parent = last_idx / 2;
    if (heap[parent] < heap[last_idx]) {
        std::swap(heap[last_idx], heap[parent]);
        sift_up(heap, parent);
    }
}

void add_to_heap(std::vector<Participant>& heap, int& last_idx, const Participant& participant) {
    heap.push_back(participant);
    last_idx++;
    sift_up(heap, last_idx);
}

void sift_down(std::vector<Participant>& heap, int first, int last_idx) {
    int left = first * 2;
    int right = first * 2 + 1;
    
    if (left > last_idx) {
        return;
    }
    
    int largest = left;
    if (right <= last_idx && heap[left] < heap[right]) {
        largest = right;
    }
    
    if (heap[first] < heap[largest]) {
        std::swap(heap[first], heap[largest]);
        sift_down(heap, largest, last_idx);
    }
}

void print_out(std::vector<Participant>& heap, int last_idx) {
    while (last_idx > 0) {
        std::cout << heap[1].name << std::endl;
        std::swap(heap[1], heap[last_idx]);
        heap.pop_back();
        last_idx--;
        sift_down(heap, 1, last_idx);
    }
}

int main() {
    std::vector<Participant> heap;
    heap.push_back(Participant(0, 0, "=)"));
    int last_idx = 0;
    
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i) {
        std::string name;
        int scores, penalty;
        std::cin >> name >> scores >> penalty;
        Participant participant(scores, penalty, name);
        add_to_heap(heap, last_idx, participant);
    }
    
    print_out(heap, last_idx);
    
    return 0;
}
```

</details>