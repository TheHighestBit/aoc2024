#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>

using namespace std;

vector<long long> readFile() {
    ifstream file("../input.txt");
    vector<long long> res;
    long long el;

    while (file >> el) {
        res.push_back(el);
    }

    return res;
}

int countDigits(const long long& num) {
    int digits = 0;
    long long temp = num;

    while (temp > 0) {
        digits++;
        temp /= 10;
    }

    return digits;
}

pair<long long, long long> splitNum(const long long& num, const int& digits) {
    const long long half = digits / 2;
    const auto divisor = static_cast<long long>(std::pow(10, half));

    long long first = num / divisor;
    long long second = num % divisor;

    return {first, second};
}

// See part2 for a better approach...
void part1(const vector<long long>& pebbles) {
    auto stones(pebbles);

    for (int i = 0; i < 25; i++) {
        cout << i << "/25" << endl;

        for (long long j = 0; j < stones.size(); j++) {
            const long long& current = stones[j];

            if (current == 0) {
                stones.at(j) = 1;
            } else {
                const int digits = countDigits(current);

                if (digits % 2 == 0) {
                    auto splitted = splitNum(current, digits);

                    stones[j] = splitted.second;
                    stones.insert(stones.begin() + j, splitted.first);

                    j++;
                } else {
                    auto num = current * 2024;

                    stones[j] = num;
                }
            }
        }

        // for (const auto c : stones) {
        //     cout << c << " ";
        // }
        //
        // cout << endl;
    }

    cout << "Part1: " << stones.size() << endl;
}

void part2(const vector<long long>& pebbles) {
    unordered_map<long long, long long> current;
    unordered_map<long long, long long> next;

    for (const auto& c : pebbles) {
        current[c]++;
    }

    for (int i = 0; i < 75; i++) {
        next.clear();

        for (const auto& [stone, count] : current) {
            if (stone == 0) {
                next[1] += count;
            } else {
                const auto digits = countDigits(stone);

                if (digits % 2 == 0) {
                    auto [left, right] = splitNum(stone, digits);

                    next[left] += count;
                    next[right] += count;
                } else {
                    next[stone * 2024] += count;
                }
            }
        }

        current = move(next);
    }

    long long total = 0;

    for (const auto& [_, count] : current) {
        total += count;
    }

    cout << "Part2: " << total << endl;
}

int main() {
    const auto pebbles = readFile();

    part1(pebbles);
    part2(pebbles);
}