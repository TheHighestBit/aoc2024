#include <climits>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<vector<char>> readFile() {
    ifstream file("../input.txt");
    vector<vector<char>> res;
    string line;

    while (getline(file, line)) {
        vector<char> inner;

        for (auto c : line) {
            inner.push_back(c);
        }

        res.push_back(inner);
    }

    return res;
}

// Really stupid approach, for some reason I thought this would be better O() than the simulation...
void part1(const vector<vector<char>> &map) {
    auto vis(map);
    int startx, starty, dirx, diry;
    vector<pair<int, int>> obstacles;
    int M = map.size();
    int N = map[0].size();

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            char current = map[y][x];

            if (current == '#') {
                obstacles.push_back({x, y});
            } else if (current != '.') {
                startx = x;
                starty = y;

                if (current == '^') {
                    dirx = 0;
                    diry = -1;
                } else if (current == '>') {
                    dirx = 1;
                    diry = 0;
                } else if (current == '<') {
                    dirx = -1;
                    diry = 0;
                } else {
                    dirx = 0;
                    diry = 1;
                }
            }
        }
    }

    set<pair<int, int>> visited = {{startx, starty}};
    while (true) {
        pair<int, int> closest = {INT_MAX, INT_MAX};
        for (int i = 0; i < obstacles.size(); i++) {
            auto obstacle = obstacles[i];
            if (dirx != 0 && obstacle.second == starty) { // Need to consider rows
                if (dirx > 0 && obstacle.first > startx && obstacle.first < closest.first || dirx < 0 && obstacle.first < startx && (obstacle.first > closest.first || closest.first == INT_MAX)) {
                    closest.first = obstacle.first;
                }
            } else if (diry != 0 && obstacle.first == startx) {
                if (diry > 0 && obstacle.second > starty && obstacle.second < closest.second || diry < 0 && obstacle.second < starty && (obstacle.second > closest.second || closest.second == INT_MAX)) {
                    closest.second = obstacle.second;
                }
            }
        }

        if (closest.first != INT_MAX) {
            if (dirx < 0) {
                for (int i = startx - 1; i > closest.first; i--) {
                    visited.insert({i, starty});
                }

                dirx = 0;
                diry = -1;
                startx = closest.first + 1;
            } else {
                for (int i = startx + 1; i < closest.first; i++) {
                    visited.insert({i, starty});
                }

                dirx = 0;
                diry = 1;
                startx = closest.first - 1;
            }
        } else if (closest.second != INT_MAX) {
            if (diry < 0) {
                for (int i = starty - 1; i > closest.second; i--) {
                    visited.insert({startx, i});
                }

                dirx = 1;
                diry = 0;
                starty = closest.second + 1;
            } else {
                for (int i = starty + 1; i < closest.second; i++) {
                    visited.insert({startx, i});
                }

                dirx = -1;
                diry = 0;
                starty = closest.second - 1;
            }
        } else {
            break;
        }

        // for (auto visit : visited) {
        //     vis[visit.second][visit.first] = 'X';
        // }

        // for (auto row : vis) {
        //     for (auto c : row) {
        //         cout << c;
        //     }

        //     cout << endl;
        // }

        // cout << "----------------------------------" << endl;
    }

    if (dirx < 0) {
        while (startx >= 0) {
            visited.insert({startx, starty});
            startx--;
        }
    } else if (dirx > 0) {
        while (startx < N) {
            visited.insert({startx, starty});
            startx++;
        }
    } else if (diry < 0) {
        while (starty >= 0) {
            visited.insert({startx, starty});
            starty--;
        }
    } else {
        while (starty < M) {
            visited.insert({startx, starty});
            starty++;
        }
    }

    cout << "Part1: " << visited.size() << endl;
}

// This is chatGPT generated, I should have used this approach in part1 but oh well...
bool runSimulation(const vector<vector<char>> &map, int x, int y, int xdir, int ydir) {
    int M = (int)map.size();
    int N = (int)map[0].size();

    // Directions in order: up, right, down, left
    // We will use these to rotate the direction to the right when needed.
    vector<pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int dirIndex = 0;
    // Find which dirIndex matches (xdir, ydir)
    for (int i = 0; i < 4; i++) {
        if (directions[i].first == xdir && directions[i].second == ydir) {
            dirIndex = i;
            break;
        }
    }

    // Set of visited states: (x, y, dirIndex)
    set<tuple<int, int, int>> visitedStates;
    visitedStates.insert({x, y, dirIndex});

    while (true) {
        int nx = x + directions[dirIndex].first;
        int ny = y + directions[dirIndex].second;

        // Check if leaving the map
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) {
            // No loop since we exited
            return false;
        }

        // Check what is ahead
        char frontCell = map[ny][nx];
        // Treat direction symbols as empty cells
        if (frontCell == '^' || frontCell == '>' || frontCell == 'v' || frontCell == '<') {
            frontCell = '.';
        }

        if (frontCell == '#') {
            // Obstacle ahead, turn right
            dirIndex = (dirIndex + 1) % 4;
        } else {
            // Move forward
            x = nx;
            y = ny;
        }

        // Check if we have seen this state before
        auto state = make_tuple(x, y, dirIndex);
        if (visitedStates.find(state) != visitedStates.end()) {
            // We have a loop
            return true;
        }
        visitedStates.insert(state);
    }

    // Theoretically unreachable, since we either return false by exiting map or return true when looping
    return false;
}

bool isInSet(const set<pair<int, int>> &seen, int x, int y) {
    for (auto el : seen) {
        if (el.first == x && el.second == y) {
            return true;
        }
    }

    return false;
}

void part2(vector<vector<char>> &map) {
    int startx, starty;
    int dirx, diry;
    int M = map.size();
    int N = map[0].size();

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            char current = map[y][x];

            if (current != '.' && current != '#') {
                startx = x;
                starty = y;

                if (current == '^') {
                    dirx = 0;
                    diry = -1;
                } else if (current == '>') {
                    dirx = 1;
                    diry = 0;
                } else if (current == '<') {
                    dirx = -1;
                    diry = 0;
                } else {
                    dirx = 0;
                    diry = 1;
                }
            }
        }
    }

    set<pair<int, int>> seen;
    int xorg = startx;
    int yorg = starty;
    int orgdirx = dirx;
    int orgdiry = diry;

    while (true) {
        startx += dirx;
        starty += diry;

        if (startx == xorg && starty == yorg || isInSet(seen, startx, starty)) {
            continue;
        }

        if (startx < 0 || startx >= N || starty < 0 || starty >= M) {
            break;
        } else {
            if (map[starty][startx] != '#') {
                map[starty][startx] = '#';

                if (runSimulation(map, xorg, yorg, orgdirx, orgdiry))
                    seen.insert({startx, starty});
                map[starty][startx] = '.';
            } else {
                startx -= dirx;
                starty -= diry;

                if (dirx > 0) {
                    dirx = 0;
                    diry = 1;
                } else if (dirx < 0) {
                    dirx = 0;
                    diry = -1;
                } else if (diry > 0) {
                    dirx = -1;
                    diry = 0;
                } else {
                    dirx = 1;
                    diry = 0;
                }
            }
        }
    }

    cout << "Part2: " << seen.size() << endl;
}

int main() {
    auto map = readFile();

    part1(map);
    part2(map);
}
