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