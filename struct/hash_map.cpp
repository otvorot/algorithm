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