#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <set>

using namespace std;

vector<vector<char>> readFile() {
    ifstream file("../input.txt");
    vector<vector<char>> res;
    string line;

    while (getline(file, line)) {
        vector<char> inner;

        for (const auto& c : line) {
            inner.push_back(c);
        }

        res.push_back(inner);
    }

    return res;
}

#include <bits/stdc++.h>
using namespace std;

void part1(const vector<vector<char>>& grid) {
    set<pair<int, int>> antinodes;
    map<char, vector<pair<int, int>>> antennas;
    auto vis = grid;
    const int M = grid.size();
    const int N = grid[0].size();

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            char id = grid[y][x];
            if (id != '.') {
                if (antennas.find(id) != antennas.end()) {
                    for (const auto& antenna : antennas[id]) {
                        int ax = antenna.first;
                        int ay = antenna.second;

                        int node1x = 2*ax - x;
                        int node1y = 2*ay - y;
                        int node2x = 2*x - ax;
                        int node2y = 2*y - ay;

                        if (node1x >= 0 && node1x < N && node1y >= 0 && node1y < M) {
                            antinodes.insert({node1x, node1y});
                            vis[node1y][node1x] = '#';
                        }
                        if (node2x >= 0 && node2x < N && node2y >= 0 && node2y < M) {
                            antinodes.insert({node2x, node2y});
                            vis[node2y][node2x] = '#';
                        }
                    }

                    antennas[id].emplace_back(x, y);
                } else {
                    antennas[id] = {{x, y}};
                }
            }
        }
    }

    /*for (const auto& row : vis) {
        for (char c : row) {
            cout << c;
        }
        cout << "\n";
    }*/

    cout << "Part1: " << antinodes.size() << endl;
}

struct Line {
    int dx, dy, c;
    bool operator<(const Line &o) const {
        if (dx != o.dx) return dx < o.dx;
        if (dy != o.dy) return dy < o.dy;
        return c < o.c;
    }
};

void part2(const vector<vector<char>>& grid) {
    int M = (int)grid.size();
    int N = (int)grid[0].size();

    map<char, vector<pair<int,int>>> antennas;
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            char c = grid[y][x];
            if (c != '.') antennas[c].push_back({x,y});
        }
    }

    set<pair<int,int>> antinodes;
    auto vis = grid;
    map<char, set<Line>> linesByFreq;

    for (auto &kv : antennas) {
        char freq = kv.first;
        const auto &coords = kv.second;

        if (coords.size() < 2) continue;

        for (int i = 0; i < (int)coords.size(); i++) {
            for (int j = i+1; j < (int)coords.size(); j++) {
                int xA = coords[i].first;
                int yA = coords[i].second;
                int xB = coords[j].first;
                int yB = coords[j].second;

                int dx = xB - xA;
                int dy = yB - yA;
                int g = std::gcd(dx, dy);
                dx /= g; dy /= g;

                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx; dy = -dy;
                }

                int c = dy*xA - dx*yA;

                Line line{dx, dy, c};
                linesByFreq[freq].insert(line);
            }
        }
    }

    for (auto &kv : linesByFreq) {
        for (auto &line : kv.second) {
            int dx = line.dx;
            int dy = line.dy;
            int c = line.c;

            if (dx == 0) {
                // Vertical line: X is fixed.
                // dy*x - dx*y = c => dy*X = c since dx=0
                // X can be found from c/dy, must be integer
                if (c % dy == 0) {
                    int X = c/dy;
                    if (X >= 0 && X < N) {
                        for (int Y = 0; Y < M; Y++) {
                            antinodes.insert({X,Y});
                            vis[Y][X] = '#';
                        }
                    }
                }
            } else if (dy == 0) {
                // Horizontal line: Y is fixed.
                // dy*X - dx*Y = c => -dx*Y = c => Y = -c/dx
                if (c % dx == 0) {
                    int Y = -c/dx;
                    if (Y >= 0 && Y < M) {
                        for (int X = 0; X < N; X++) {
                            antinodes.insert({X,Y});
                            vis[Y][X] = '#';
                        }
                    }
                }
            } else {
                // General line:
                // dy*X - dx*Y = c
                // Solve for Y: Y = (dy*X - c)/dx
                // We'll iterate over X and check if Y is an integer within bounds.
                // Alternatively, if |dx| > |dy|, we might iterate over Y to reduce checks.
                // We'll just iterate over all X for simplicity.

                for (int X = 0; X < N; X++) {
                    int numerator = dy*X - c;
                    if (numerator % dx == 0) {
                        int Y = numerator / dx;
                        if (Y >= 0 && Y < M) {
                            antinodes.insert({X,Y});
                            vis[Y][X] = '#';
                        }
                    }
                }
            }
        }
    }

    /*for (auto &row : vis) {
        for (auto &c : row) cout << c;
        cout << "\n";
    }*/

    cout << "Part2: " << antinodes.size() << "\n";
}


int main() {
    const auto map = readFile();

    part1(map);
    part2(map);
}