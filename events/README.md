# сортировки событий


<details>
<summary>автоспорт</summary>

## условие
В кружке автомоделирования проводятся соревнования. Они проходят на прямом участке трассы длиной ***L*** и шириной ***W***. ***N*** участников выставляют свои модели на стартовые позиции. По свистку все модели начинают движение.

Цель состязания — быстрее всех доехать до линии финиша. Однако в пути каждую модель подстерегают опасности. А именно, модель может врезаться в борта трассы и тем самым выбывать из гонки, или две и более модели могут столкнуться и также выбыть из гонки. Выбывшие из гонки модели убираются с трассы.

Введем систему координат, в которой ось ***OX*** будет направлена вдоль протяжения трассы, а ось ***OY*** — поперек ему. Тогда трасса является прямоугольником, ограниченным прямыми ***y = 0***, ***y = W***, ***x = 0*** и ***x = L***.

Модель считается врезавшейся в борт трассы, если в некоторый момент времени её ***y***-координата будет равна либо ***0***, либо ***W***. Две модели считаются столкнувшимися, если в некоторый момент времени их координаты совпадают. Модели можно считать материальными точками.

Модель побеждает в соревновании, если она успешно преодолела линию финиша (прямую ***x = L***) и сделала это не позже любой другой модели. Возможно, что побеждает сразу несколько модели, в этом случае, как говорится, «побеждает дружба». Возможно также, что ни одна модель по тем или иным причинам не сумеет преодолеть линию финиша.

Заметим отдельно, что если модель проходит через какую-либо из точек ***(L, 0)*** или ***(L, W)***, то считается, что она врезается в борт. Если две или более модели сталкиваются непосредственно на линии финиша, то они не считаются финишировавшими.

Поведение большинства моделей довольно предсказуемо, поэтому часто можно предугадать ход состязания. В данной задаче мы будем приближенно считать, что все модели начинают двигаться из своих начальных точек с заданными, постоянными на протяжении соревнования, векторами скорости.

Формат ввода:

В первой строке вводятся три числа ***N***, ***L***, ***W***. (***1 ≤ N ≤ 1000***, ***1 ≤ L ≤ 10⁴***, ***2 ≤ W ≤ 10⁴***).

В последующих ***N*** строках вводятся описания соревнующихся моделей: по 4 целых числа ***xᵢ***, ***yᵢ***, ***vxᵢ***, ***vyᵢ***, ***1 ≤ i ≤ N***. (***xᵢ***, ***yᵢ***) — это координаты стартовой точки модели с номером ***i***, (***vxᵢ***, ***vyᵢ***) — вектор скорости этой модели.

Гарантируется, что стартовые точки всех моделей различны, находятся на трассе, и не располагаются ни на каком-либо борту трассы, ни на линии финиша. Координаты векторов скорости не превышают ***10⁴*** по абсолютному значению.

Формат вывода:

В первой строке выведите количество победителей. Во второй строке выведите их номера в порядке возрастания.


## идея решения
Алгоритм моделирует гонку через события во времени. Для каждой модели вычисляются:

Время финиша (x = L)

Время столкновения с бортом (*y = 0* или y = W)

Время столкновения с другими моделями

События сортируются по времени, и модели последовательно исключаются при столкновениях. Победителями становятся модели, которые первыми достигают финиша без исключения.

Сложность:

Время: O(N²) — из-за попарной проверки столкновений между моделями

Память: O(N²) — хранение всех возможных событий столкновений


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


struct Point {
    int name;
    double x;
    double y;
    double vx;
    double vy;

    Point(int a, double b, double c, double d, double(e)) : name(a), x(b), y(c), vx(d), vy(e) {}

    double timeFinish(double L) {
        if (vx <= 0) return -1;
        return (L - x) / vx;
    }

    double timeSide(double W) {
        if (!vy) {
            return 0;
        } else if (vy < 0) {
            return y / -vy;
        } else {
            return (W - y) / vy;
        }
    }

    double timeCollision(const Point& other) {
        
        double dx = other.x - x;
        double dy = other.y - y;
        double dvx = vx - other.vx;
        double dvy = vy - other.vy;

        double tx = dvx ? dx / dvx : 0;
        double ty = dvy ? dy / dvy : 0;

        if (tx > 0 && ty > 0 && tx == ty) return tx;

        if (tx < 0 || ty < 0) return 0;

        double t = std::max(tx, ty);
        if (x + vx * t == other.x + other.vx * t && y + vy * t == other.y + other.vy * t) {
            return t;
        }

        return 0;
    }
};

struct Event {
    int name;
    double time;
    short type;
    int other;

    Event(int n, double t, short ty, int o) : name(n), time(t), type(ty), other(o) {}
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(10);

    int n;
    double L, W;
    std::cin >> n >> L >> W;
    
    std::vector<Point> points;
    std::vector<Event> events;
    events.reserve(n * 2);
    points.reserve(n);

    double a, b, c, d;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a >> b >> c >> d;
        points.emplace_back(Point(i, a, b, c, d));
    }

    for (int i = 0; i < n; ++i) {
        if (double time = points[i].timeFinish(L); time > 0) {
            events.emplace_back(Event(points[i].name, time, 2, 0));
        }

        if (double time = points[i].timeSide(W); time) {
            events.emplace_back(Event(points[i].name, time, 1, 0));
        }

        for (int j = i + 1; j < n; ++j) {
            if (double time = points[i].timeCollision(points[j]); time) {
                events.emplace_back(Event(points[i].name, time, 0, points[j].name));
                events.emplace_back(Event(points[j].name, time, 0, points[i].name));
            }
        }
    }

    std::sort(
        events.begin(),
        events.end(),
        [] (const Event& lhs, const Event& rhs) {
            if (lhs.time == rhs.time) {
                return lhs.type < rhs.type;
            }
            return lhs.time < rhs.time;
        }
    );

    std::vector<double> outsiders(n + 1, false);
    std::vector<int> winners;
    winners.reserve(n);
    for (int i = 0; i < events.size(); ++i) {
        const double& time = events[i].time;
        const int& me = events[i].name;

        if (outsiders[me]) continue;
        const int& other = events[i].other;
        const short& type = events[i].type;
        if (!type) {
            if (!outsiders[other] || outsiders[other] == time) {
                outsiders[me] = time;
            }
        }

        if (type == 1) outsiders[me] = time;

        if (type == 2) {
            int j = i;
            while (j < events.size() && events[j].time == time) {
                if (events[j].type == 2 && !outsiders[events[j].name]) {
                    winners.emplace_back(events[j].name);
                }
                ++j;
            }
            break;
        }
    }

    std::sort(winners.begin(), winners.end());

    std::cout << winners.size() << '\n';
    for (auto& x : winners) {
        std::cout << x << ' ';
    }

}
```

</details>


<details>
<summary>рейсы между офисами</summary>

## условие
У компании открылся второй офис, и для перемещения сотрудников между офисами было решено организовать автобусные рейсы по расписанию — из первого офиса во второй и обратно. Расписание уже готово, но необходимо определить, каким **минимальным количеством автобусов** можно обойтись, чтобы обслужить все рейсы в течение одного дня.

Расписание состоит из:
- ***N*** рейсов из **первого офиса** во **второй**,
- ***M*** рейсов из **второго офиса** в **первый**.

Для каждого рейса известны:
- **время отправления**,
- **время прибытия**,  
оба — с точностью до минуты, в формате `HH:MM`.

Ограничения
- Каждый рейс происходит **в пределах одних календарных суток** (с `00:00` до `23:59` включительно).
- Ни один рейс не длится менее одной минуты: время прибытия **строго больше** времени отправления.
- Автобус, прибывший в офис в минуту ***t***, **может сразу отправиться** в новый рейс, начинающийся в ту же минуту ***t***.
- Одновременно у офиса может находиться, отправляться или прибывать **любое количество автобусов**.
- Автобусы **не могут ездить вне расписания** — только по запланированным рейсам.
- Не требуется учитывать состояние автобусов на следующий день — нужно рассчитать количество автобусов **только для одного дня**.

---

Формат ввода

- Первая строка: целое число ***N*** — количество рейсов из первого офиса во второй ($1 \leq N \leq 10^5$).
- Следующие ***N*** строк: каждый рейс в формате  
  `HH:MM-HH:MM` — **отправление из первого офиса — прибытие во второй**.
- Далее строка с целым числом ***M*** — количество обратных рейсов ($1 \leq M \leq 10^5$).
- Следующие ***M*** строк: каждый обратный рейс в том же формате  
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
<summary>ремонт выбоин</summary>

## условие
Прямая трасса состоит из ***n*** участков, по ней проложено ***m*** автобусных маршрутов. Участки на трассе пронумерованы числами от ***1*** до ***n*** слева направо, маршруты пронумерованы от ***1*** до ***m***. Маршрут ***i*** проходит по участкам с ***l_i*** по ***r_i*** включительно. На ***j***-м участке изначально расположено ***a_j*** выбоин. Дискомфорт от поездки по маршруту равен суммарному количеству выбоин на участках, по которым проходит маршрут.

В бюджете автодорожного предприятия есть средства на ремонт не более чем ***k*** выбоин (естественно, количество выбоин на участке не может стать отрицательным). Определите, какой минимальной суммы дискомфорта от поездок по всем маршрутам можно добиться.

Формат ввода

В первой строке вводятся три числа ***n***, ***m*** и ***k*** — количество участков трассы, маршрутов и количество выбоин, которые можно починить (***1 ≤ n ≤ 10⁵***, ***1 ≤ m ≤ 10⁶***, ***0 ≤ k ≤ 10¹²***).

Во второй строке вводится ***n*** целых чисел ***a_i*** — количество выбоин на участках трассы (***0 ≤ a_i ≤ 10⁷***).

В следующих ***m*** строках вводится по два числа ***l_i*** и ***r_i***, задающие начальный и конечный участок каждого из маршрутов (***1 ≤ l_i ≤ r_i ≤ n***).

Формат вывода

Выведите минимальный суммарный дискомфорт на маршрутах после ремонта выбоин в пределах бюджета.


## идея решения
Сортируем события по времени. Сканирующая линия - определяем "важность" каждого участка (сколько маршрутов через него проходит). 
 - Начало маршрута: +1 к счетчику
 - Конец маршрута: -1 к счетчику

Сортировка - упорядочиваем участки по убыванию важности. Самые "популярные" участки - в начале. Оптимальный ремонт - ремонтируем выбоины в порядке убывания важности:
 - Сначала чиним самые загруженные участки
 - Пока не закончатся деньги (k) или выбоины

Суть: Максимальная выгода от ремонта достигается, когда мы чиним те участки, которые влияют на наибольшее количество маршрутов.


```cpp
#include <iostream>
#include <algorithm>
#include <vector>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    long long k;
    std::cin >> n >> m >> k;

    std::vector<std::pair<long long, long long>> origin(n + 2);
    std::vector<std::pair<int, short>> events;
    events.reserve(m * 2);

    for (int i = 1; i <= n; ++i) {
        std::cin >> origin[i].first;
    }

    int l, r;
    for (int i = 0; i < m; ++i) {
        std::cin >> l >> r;
        events.emplace_back(l, 1);
        events.emplace_back(r + 1, -1);
    }

    std::sort(
        events.begin(),
        events.end(),
        [] (const std::pair<int, short>& lhs, const std::pair<int, short>& rhs) {
            return lhs.first < rhs.first;
        }
    );

    l = events.front().first; r = events.back().first; int j = 0;
    long long mnozh = 0;

    for (int i = l; i < r; ++i) {
        if (i == events[j].first) {
            int p = j;
            while (p < events.size() - 1 && events[j].first == events[p].first) {
                mnozh += events[p].second;
                ++p;
            }
            j = p;
        }

        origin[i].second = mnozh;
    }

    std::sort(
        origin.begin() + l,
        origin.begin() + r,
        [] (const std::pair<long long, long long>& lhs, const std::pair<long long, long long>& rhs) {
            return lhs.second > rhs.second;
        }
    );

    long long final = 0;
    for (int i = l; i < r; ++i) {
        // std::cout << origin[i].first << ' ' << origin[i].second << '\n';
        long long diff = std::min(k, origin[i].first);
        k -= diff;
        origin[i].first -= diff;
        final += origin[i].first * origin[i].second;
    }

    std::cout << final << '\n';
}
```

</details>


<details>
<summary>железнодорожный переезд</summary>

## условие
По железной дороге движутся ***n*** поездов. Каждый поезд представляет собой отрезок. Поезд с номером ***i*** в начальный момент времени занимает отрезок ***[a_i; b_i]***. Поезда не стоят на месте — ***i***-й поезд движется с постоянной скоростью ***v_i***. Железная дорога двунаправлена, то есть поезда могут двигаться как в положительном направлении оси, так и в отрицательном. Отрезки, представляющие поезда, в любой момент времени могут пересекаться, вкладываться друг в друга и совпадать.

В точке ***x*** находится железнодорожный переезд, к которому в моменты ***t_i*** подъезжают машины. Для каждой машины требуется вычислить минимальный момент времени, в который она сможет пересечь железнодорожный переезд.

Машина может пересечь переезд, если он не занят поездом. Переезд считается занятым, если отрезок, представляющий собой некоторый поезд, содержит в себе точку ***x***. Причем если поезд подъезжает к перекрестку одновременно с машиной, то переезд считается занятым. Машины пересекают переезд мгновенно.

Формат ввода

В первой строке вводится три целых числа — ***n***, ***m*** и ***x*** (***1 ≤ n, m ≤ 10⁵***, ***|x| ≤ 10⁹***) — количество поездов, движущихся по железной дороге, количество машин, подъезжающих к железнодорожному переезду и точка, в которой находится переезд.

В следующих ***n*** строках содержатся по три целых числа ***a_i***, ***b_i***, ***v_i*** (***|a_i| ≤ 10⁹***, ***|b_i| ≤ 10⁹***, ***1 ≤ v_i ≤ 10⁹***, ***a_i ≠ b_i***) — отрезок, задающий поезд и его скорость движения. Если ***a_i < b_i***, то поезд движется в положительном направлении оси, если ***a_i > b_i*** — в отрицательном.

В следующей строке находятся ***m*** неотрицательных целых чисел ***t_j*** (***0 ≤ t_j ≤ 10⁹***) — моменты времени, в которые к переезду подъедут машины.

Формат вывода

В ***m*** строках выходного файла выведите ***m*** вещественных чисел ***b_j*** — минимальный момент времени, в который ***j***-я машина сможет пересечь железнодорожный переезд. Ответ будет считаться правильным, если относительная или абсолютная погрешность каждого ***b_j*** не превосходит ***10⁻⁶***.


## идея решения
1. Преобразование задачи: Для каждого поезда вычисляем временной интервал, когда он занимает переезд в точке x.

2. Объединение интервалов: Сортируем все интервалы занятости по началу и объединяем пересекающиеся.

3. Бинарный поиск: Для каждой машины ищем интервал занятости, в который попадает время ее прибытия:

Если время до всех интервалов → можно ехать сразу

Если внутри интервала → ждем конца интервала

Если после интервала → можно ехать сразу

Сложность:
O(n log n) - сортировка интервалов занятости

O(n) - объединение интервалов

O(m log n) - бинарный поиск для каждой машины

Итого: O((n + m) log n)

Ключевые моменты:
Поезд занимает переезд, когда его движущийся отрезок покрывает точку x

Интервалы занятости могут пересекаться → объединяем в непрерывные блоки

Машина ждет только если приезжает во время занятости переезда


```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nTrain, mCar, point;
    std::cin >> nTrain >> mCar >> point;

    std::vector<std::pair<double, double>> occupied;
    occupied.reserve(nTrain);

    for (int i = 0; i < nTrain; ++i) {
        double x, y, v;
        std::cin >> x >> y >> v;
        
        double t1, t2;
        if (x < y) {
            t1 = (point - y) / v;
            t2 = (point - x) / v;
        } else {
            t1 = (y - point) / v;
            t2 = (x - point) / v;
        }
        
        if (t2 < 0) continue;
        
        if (t1 < 0) t1 = 0;
        
        occupied.emplace_back(t1, t2);
    }

    std::sort(occupied.begin(), occupied.end());

    std::vector<std::pair<double, double>> merged;
    for (const auto& interval : occupied) {
        if (merged.empty() || merged.back().second < interval.first) {
            merged.push_back(interval);
        } else {
            merged.back().second = std::max(merged.back().second, interval.second);
        }
    }

    double checkTime;
    std::cout << std::fixed << std::setprecision(10);
    for (int i = 0; i < mCar; ++i) {
        std::cin >> checkTime;
        
        auto it = std::upper_bound(
            merged.begin(), merged.end(), checkTime,
            [](double t, const std::pair<double, double>& interval) {
                return t < interval.first;
            }
        );
        
        if (it == merged.begin()) {
            std::cout << checkTime << '\n';
        } else {
            --it;
            if (checkTime <= it->second) {
                std::cout << it->second << '\n';
            } else {
                std::cout << checkTime << '\n';
            }
        }
    }

    return 0;
}
```

</details>