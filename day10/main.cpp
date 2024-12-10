#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

vector<vector<int>> readFile() {
    ifstream file("../input.txt");
    vector<vector<int>> res;
    string line;

    while (getline(file, line)) {
        vector<int> inner;

        for (const auto& c : line) {
            inner.emplace_back(c - '0');
        }

        res.emplace_back(inner);
    }

    return res;
}

int findRoutes1(const vector<vector<int>>& map, int x, int y, int last, set<pair<int, int>>& seen) {
    if (x >= 0 && x < map[0].size() && y >= 0 && y < map.size() && map[y][x] == last + 1) {
        if (map[y][x] == 9) {
            if (!seen.contains({ x, y })) {
                seen.insert({ x, y });
                return 1;
            }

            return 0;
        }

        int current = map[y][x];
        int total = 0;

        total += findRoutes1(map, x + 1, y, current, seen);
        total += findRoutes1(map, x - 1, y, current, seen);
        total += findRoutes1(map, x, y + 1, current, seen);
        total += findRoutes1(map, x, y - 1, current, seen);

        return total;
    }

    return 0;
}

int findRoutes2(const vector<vector<int>>& map, int x, int y, int last) {
    if (x >= 0 && x < map[0].size() && y >= 0 && y < map.size() && map[y][x] == last + 1) {
        if (map[y][x] == 9) {
            return 1;
        }

        int current = map[y][x];
        int total = 0;

        total += findRoutes2(map, x + 1, y, current);
        total += findRoutes2(map, x - 1, y, current);
        total += findRoutes2(map, x, y + 1, current);
        total += findRoutes2(map, x, y - 1, current);

        return total;
    }

    return 0;
}

void part1(const vector<vector<int>>& map) {
    int res = 0;
    set<pair<int, int>> seen;

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == 0) {
                int result = findRoutes1(map, x, y, -1, seen);
                res += result;

                seen.clear();
            }
        }
    }

    cout << "Part1: " << res << endl;
}

void part2(const vector<vector<int>>& map) {
    int res = 0;

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == 0) {
                int result = findRoutes2(map, x, y, -1);

                res += result;
            }
        }
    }

    cout << "Part2: " << res << endl;
}

int main() {
    const auto map = readFile();

    part1(map);
    part2(map);
}