#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;
typedef pair<int, int> Point;
const vector<Point> directions = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

vector<vector<char>> readFile() {
    ifstream file("../input.txt");
    vector<vector<char>> res;
    string line;

    while (getline(file, line)) {
        vector<char> inner;
        for (const auto c : line) {
            inner.push_back(c);
        }

        res.push_back(inner);
    }

    return res;
}

set<Point> floodFill(const vector<vector<char>>& map, set<Point>& seen, int x, int y, char current) {
    set<Point> res;
    const int M = map.size();
    const int N = map[0].size();

    if (x < 0 || x >= N || y < 0 || y >= M || map[y][x] != current) {
        return {};
    }

    res.insert({ x, y });
    seen.insert({ x, y });

    for (const auto& [fst, snd] : directions) {
        const int newX = x + fst;
        const int newY = y + snd;

        if (!seen.contains({ newX, newY })) {
            const auto temp = floodFill(map, seen, newX, newY, current);
            res.insert(temp.begin(), temp.end());
        }
    }

    return res;
}

// Main idea is that every adjacent pair of points in the plot will reduce the perimeter by 2 (no fence between them)
int calculatePerimeter(const set<Point>& plot) {
    int adjecent_pairs = 0;

    for (const auto [x, y] : plot) {
        if (plot.contains({ x + 1, y })) {
            adjecent_pairs++;
        }

        if (plot.contains({ x, y + 1})) {
            adjecent_pairs++;
        }
    }

    const int total = plot.size() * 4;
    return total - 2 * adjecent_pairs;
}

const vector<Point> SIDE_DIRS = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

// This doesn't handle cases where there is also fencing on the inside of the perimeter...
// Don't have any more time to work on this, might come back to it later.
int calculateSides(const set<Point>& plot) {
    Point start = { INT_MAX, INT_MAX };
    int sides = 0;

    for (const auto& [x, y] : plot) {
        if (x < start.first || (x == start.first && y < start.second)) {
            start = { x, y };
        }
    }

    Point current = start;
    int current_dir = 0;

    while (true) {
        if (current == start && current_dir % 4 == 0 && sides > 0) {
            break;
        }

        // First we check if we can make a left turn from here
        Point left_check = { current.first + SIDE_DIRS[(current_dir + 3) % 4].first, current.second + SIDE_DIRS[(current_dir + 3) % 4].second };
        if (plot.contains(left_check)) {
            current_dir = (current_dir + 3) % 4;
            current = left_check;
            sides++;
            continue;
        }

        const Point next = { current.first + SIDE_DIRS[current_dir].first, current.second + SIDE_DIRS[current_dir].second };

        if (!plot.contains(next)) {
            sides++;

            // First check for left turn
            if (plot.contains({ current.first + SIDE_DIRS[(current_dir + 3) % 4].first, current.second + SIDE_DIRS[(current_dir + 3) % 4].second })) {
                current_dir = (current_dir + 3) % 4;
            } else if (plot.contains({ current.first + SIDE_DIRS[(current_dir + 1) % 4].first, current.second + SIDE_DIRS[(current_dir + 1) % 4].second })) {
                current_dir = (current_dir + 1) % 4;
            } else { // Can't turn left or right, must turn back
                current_dir = (current_dir + 2) % 4;
                sides += 1;
            }
        } else {
            current = next;
        }

    }

    return sides;
}

void part1(const vector<vector<char>>& map) {
    unordered_map<char, vector<set<Point>>> plots;
    set<Point> seen;
    const int M = map.size();
    const int N = map[0].size();
    long long result = 0;

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            if (!seen.contains({ x, y })) {
                auto temp = floodFill(map, seen, x, y, map[y][x]);
                plots[map[y][x]].push_back(temp);
            }
        }
    }

    for (const auto [key, value] : plots) {
        for (const auto& plot : value) {
            result += plot.size() * calculatePerimeter(plot);
        }
    }

    cout << "Part1: " << result << endl;
}

void part2(const vector<vector<char>>& map) {
    unordered_map<char, vector<set<Point>>> plots;
    set<Point> seen;
    const int M = map.size();
    const int N = map[0].size();
    long long result = 0;

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            if (!seen.contains({ x, y })) {
                auto temp = floodFill(map, seen, x, y, map[y][x]);
                plots[map[y][x]].push_back(temp);
            }
        }
    }

    for (const auto [key, value] : plots) {
        for (const auto& plot : value) {
            result += plot.size() * calculateSides(plot);
        }
    }

    cout << "Part2: " << result << endl;
}

int main() {
    const auto map = readFile();

    part1(map);
    part2(map);
}