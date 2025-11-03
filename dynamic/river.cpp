#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string river;
    std::cin >> river;

    int leftPrev = 0, rightPrev = 1;
    int leftNow = 0, rightNow = 0;
    int leftTemp, rightTemp;

    for (short i = 0; i < river.size(); ++i) {
        if (river[i] == 'L') {
            leftNow = 1;
        } else if (river[i] == 'R') {
            rightNow = 1;
        } else {
            leftNow = 1;
            rightNow = 1;
        }

        leftTemp = std::min((leftPrev + leftNow), (rightPrev + rightNow + 1));
        rightTemp = std::min((rightPrev + rightNow), (leftPrev + leftNow + 1));

        leftPrev = leftTemp; rightPrev = rightTemp;

        leftNow = 0; rightNow = 0;
    }

    std::cout << rightPrev << '\n';
}