# сортировки событий


<details>
<summary>рейсы между офисами</summary>

## условие
У компании открылся второй офис, и для перемещения сотрудников между офисами было решено организовать автобусные рейсы по расписанию — из первого офиса во второй и обратно. Расписание уже готово, но необходимо определить, каким **минимальным количеством автобусов** можно обойтись, чтобы обслужить все рейсы в течение одного дня.

Расписание состоит из:
- ***$N$*** рейсов из **первого офиса** во **второй**,
- ***$M$*** рейсов из **второго офиса** в **первый**.

Для каждого рейса известны:
- **время отправления**,
- **время прибытия**,  
оба — с точностью до минуты, в формате `HH:MM`.

Ограничения
- Каждый рейс происходит **в пределах одних календарных суток** (с `00:00` до `23:59` включительно).
- Ни один рейс не длится менее одной минуты: время прибытия **строго больше** времени отправления.
- Автобус, прибывший в офис в минуту ***$t$***, **может сразу отправиться** в новый рейс, начинающийся в ту же минуту ***$t$***.
- Одновременно у офиса может находиться, отправляться или прибывать **любое количество автобусов**.
- Автобусы **не могут ездить вне расписания** — только по запланированным рейсам.
- Не требуется учитывать состояние автобусов на следующий день — нужно рассчитать количество автобусов **только для одного дня**.

---

Формат ввода

- Первая строка: целое число ***$N$*** — количество рейсов из первого офиса во второй ($1 \leq N \leq 10^5$).
- Следующие ***$N$*** строк: каждый рейс в формате  
  `HH:MM-HH:MM` — **отправление из первого офиса — прибытие во второй**.
- Далее строка с целым числом ***$M$*** — количество обратных рейсов ($1 \leq M \leq 10^5$).
- Следующие ***$M$*** строк: каждый обратный рейс в том же формате  
  `HH:MM-HH:MM` — **отправление из второго офиса — прибытие в первый**.

---

Формат вывода

Одно целое число — **минимальное количество автобусов**, необходимое для выполнения всех рейсов.


## идея решения
переводим время в секунды, сортируем события на временной прямой. важно при сортировке помнить, что прибытие автобуса должно быть раньше отправления. в двух переменных будем хранить требуемое кол-во автобусов - если на момент начала нового рейса свободных автобусов нет, то добавляем к общему кол-ву +1. если автобус вернулся из рейса, добавляем к свободным автобусам +1

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Event {
    short time;
    short office;
    bool start;

    Event(short t, short o, bool s) : time(t), office(o), start(s) {};

    bool operator < (const Event& other) const {
        if (time == other.time) {
            return start < other.start;
        }
        return time < other.time;
    }
};

std::pair<short, short> parser(const std::string& input) {
    std::pair<short, short> result;
    
    result.first = std::stoi(input.substr(0, 2)) * 60 + std::stoi(input.substr(3, 2));
    result.second = std::stoi(input.substr(6, 2)) * 60 + std::stoi(input.substr(9, 2));

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n;

    std::vector<Event> timeline;
    timeline.reserve(n * 2);

    //                                 цикл для первого офиса
    std::string token;
    for (int i = 0; i < n; ++i) {
        std::cin >> token;
        auto [start, finish] = parser(token);
        timeline.emplace_back(Event(start, 0, 1));
        timeline.emplace_back(Event(finish, 0, 0));
    }

    //                               цикл для второго офиса
    std::cin >> m;
    timeline.reserve(2 * (n + m));
    for (int i = 0; i < m; ++i) {
        std::cin >> token;
        auto [start, finish] = parser(token);
        timeline.emplace_back(Event(start, 1, 1));
        timeline.emplace_back(Event(finish, 1, 0));
    }

    std::sort(timeline.begin(), timeline.end());

    int freeBus[2] {0};
    int totalBus[2] {0};
    for (int i = 0; i < timeline.size(); ++i) {
        short& time = timeline[i].time;
        short& office = timeline[i].office;
        bool& start = timeline[i].start;

        if (start) {
            if (freeBus[office]) {
                --freeBus[office];
            } else {
                ++totalBus[office];
            }
        } else {
            ++freeBus[(office + 1) % 2];
        }
    }

    std::cout << totalBus[0] + totalBus[1] << '\n';
}
```

</details>


<details>
<summary></summary>

## условие



## идея решения


```cpp

```

</details>