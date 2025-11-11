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