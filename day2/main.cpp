#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<int>> readFile() {
    ifstream file("../input.txt");
    string line;
    vector<vector<int>> res;

    while (getline(file, line)) {
        int val;
        vector<int> internal;
        stringstream ss(line);

        while (ss >> val) {
            internal.emplace_back(val);
        }

        res.emplace_back(internal);
    }

    return res;
}

// Function to check if a report is strictly increasing with differences <= 3
bool isIncreasing(const vector<int>& level) {
    for (size_t i = 1; i < level.size(); ++i) {
        if (level[i] <= level[i - 1] || (level[i] - level[i - 1] > 3)) {
            return false;
        }
    }
    return true;
}

// Function to check if a report is strictly decreasing with differences <= 3
bool isDecreasing(const vector<int>& level) {
    for (size_t i = 1; i < level.size(); ++i) {
        if (level[i] >= level[i - 1] || (level[i - 1] - level[i] > 3)) {
            return false;
        }
    }
    return true;
}

// Updated isSafe function returns true if the report is safe, false otherwise
bool isSafe(const vector<int>& level) {
    return isIncreasing(level) || isDecreasing(level);
}


// Part1: Count the number of reports that are safe without any modifications
void part1(const vector<vector<int>>& levels) {
    int safe = 0;

    for (const auto& level : levels) {
        if (isSafe(level)) safe++;
    }

    cout << "Part1: " << safe << endl;
}

// Part2: Count the number of reports that are safe, considering the Problem Dampener
void part2(const vector<vector<int>>& levels) {
    int safe = 0;

    for (const auto& level : levels) {
        if (isSafe(level)) {
            safe++;
            continue;
        }

        // Attempt to remove each element one by one
        for (size_t i = 0; i < level.size(); ++i) {
            vector<int> modified = level; // Create a copy
            modified.erase(modified.begin() + i); // Remove the i-th element

            if (isSafe(modified)) {
                safe++;
                break; // No need to check further removals
            }
        }
    }

    cout << "Part2: " << safe << endl;
}


int main() {
    auto levels = readFile();

    part1(levels);
    part2(levels);
}
