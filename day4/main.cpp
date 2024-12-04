#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> readFile() {
    vector<vector<char>> data;
    ifstream file("../input.txt");
    string line;

    while (getline(file, line)) {
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }

        data.push_back(row);
    }

    return data;
}

bool checkDir(const vector<vector<char>> &matrix, int x, int y, int xdir, int ydir) {
    if (matrix[y + ydir][x + xdir] == 'M' && matrix[y + 2 * ydir][x + 2 * xdir] == 'A' && matrix[y + 3 * ydir][x + 3 * xdir] == 'S') {
        return true;
    }

    return false;
}

void part1(const vector<vector<char>> &matrix) {
    int occur = 0;
    int M = matrix.size();
    int N = matrix.at(0).size();

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            if (matrix[y][x] == 'X') {
                if (y >= 3 && x >= 3 && checkDir(matrix, x, y, -1, -1)) { // Top left diag
                    occur++;
                }

                if (y >= 3 && checkDir(matrix, x, y, 0, -1)) { // Above
                    occur++;
                }

                if (y >= 3 && x <= M - 4 && checkDir(matrix, x, y, 1, -1)) { // Top right diag
                    occur++;
                }

                if (x <= M - 4 && checkDir(matrix, x, y, 1, 0)) { // Right
                    occur++;
                }

                if (y <= N - 4 && x <= M - 4 && checkDir(matrix, x, y, 1, 1)) { // Bottom right diag
                    occur++;
                }

                if (y <= N - 4 && checkDir(matrix, x, y, 0, 1)) { // Below
                    occur++;
                }

                if (y <= N - 4 && x >= 3 && checkDir(matrix, x, y, -1, 1)) { // Bottom left diag
                    occur++;
                }

                if (x >= 3 && checkDir(matrix, x, y, -1, 0)) { // Left
                    occur++;
                }
            }
        }
    }

    cout << "Part1: " << occur << endl;
}

bool isPair(const vector<pair<int, int>> &pairs, const int &y, const int &x) {
    for (auto it = pairs.begin(); it != pairs.end(); it++) {
        if (it->first == y && it->second == x) {
            return true;
        }
    }

    return false;
}

void part2(const vector<vector<char>> &matrix) {
    int occur = 0;
    int M = matrix.size();
    int N = matrix.at(0).size();
    vector<pair<int, int>> found;

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            if (matrix[y][x] == 'M') {
                if (y >= 2 && x >= 2 && checkDir(matrix, x + 1, y + 1, -1, -1)) { // Top left diag
                    found.push_back({y, x});

                    if (isPair(found, y, x - 2)) {
                        occur++;
                    }
                }

                if (y >= 2 && x <= M - 3 && checkDir(matrix, x - 1, y + 1, 1, -1)) { // Top right diag
                    found.push_back({y, x});

                    if (isPair(found, y - 2, x)) {
                        occur++;
                    }
                }

                if (y <= N - 3 && x <= M - 3 && checkDir(matrix, x - 1, y - 1, 1, 1)) { // Bottom right diag
                    found.push_back({y, x});

                    if (isPair(found, y + 2, x)) {
                        occur++;
                    }
                }

                if (y <= N - 3 && x >= 2 && checkDir(matrix, x + 1, y - 1, -1, 1)) { // Bottom left diag
                    found.push_back({y, x});

                    if (isPair(found, y, x - 2)) {
                        occur++;
                    }
                }
            }
        }
    }

    cout << "Part2: " << occur << endl;
}

int main() {
    auto const matrix = readFile();

    part1(matrix);
    part2(matrix);
}