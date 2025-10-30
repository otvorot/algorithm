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