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