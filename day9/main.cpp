#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> readFile() {
    ifstream file("../input.txt");
    vector<int> res;
    string line;

    getline(file, line);

    for (const auto& c : line) {
        res.push_back(c - '0');
    }

    return res;
}

void part1(const vector<int>& in) {
    vector<int> expansion;
    bool isBlock = true;
    int i = 0;

    for (const auto& block : in) {
        if (isBlock) {
            for (int j = 0; j < block; j++) {
                expansion.push_back(i);
            }

            i++;
            isBlock = false;
        } else {
            for (int j = 0; j < block; j++) {
                expansion.push_back(-1);
            }

            isBlock = true;
        }
    }

    int pointer = expansion.size() - 1;
    for (int j = 0; j < pointer; j++) {
        if (expansion[j] == -1) {
            swap(expansion[j], expansion[pointer]);
            pointer--;
            while (expansion[pointer] == -1) {
                pointer--;
            }
        }
    }

    long long res = 0;
    for (int j = 0; expansion[j] != -1; j++) {
        res += expansion[j] * j;
    }

    cout << "Part1: " << res << endl;
}

void prettyPrint(const vector<tuple<int, int, int>>& blocks) {
    for (const auto& block : blocks) {
        int id = get<0>(block);
        int start = get<1>(block);
        int end = get<2>(block);

        for (int i = 0; i < end - start; i++) {
            if (id == -1) {
                cout << '.';
            } else {
                cout << id;
            }
        }
    }

    cout << endl;
}

void part2(const vector<int>& in) {
    vector<tuple<long, long, long>> expansion;
    long starti = 0;
    int id = 0;

    for (int i = 0; i < in.size(); i++) {
        if (i % 2 == 0) { // Block
            expansion.push_back({ id, starti, starti + in[i] });
            id++;
            starti += in[i];
        } else if (in[i] > 0) {
            expansion.push_back({ -1, starti, starti + in[i] });
            starti += in[i];
        }
    }

    int pointer2 = expansion.size() - 1;
    while (pointer2 > 0) {
        long id2 = get<0>(expansion[pointer2]);
        long start2 = get<1>(expansion[pointer2]);
        long end2 = get<2>(expansion[pointer2]);

        if (id2 != -1) {
            long length = end2 - start2;

            // Start searching from the front
            int pointer = 0;
            while (pointer < pointer2) {
                long id = get<0>(expansion[pointer]);
                long start = get<1>(expansion[pointer]);
                long end = get<2>(expansion[pointer]);

                if (id != -1) {
                    pointer++;
                    continue;
                }

                if (end - start == length) { // Found block of right size, move it to pointer.
                    swap(expansion[pointer], expansion[pointer2]);

                    break;
                }

                if (end - start > length) { // Need to split the block
                    get<1>(expansion[pointer]) = start + length;
                    expansion.insert(expansion.begin() + pointer, expansion[pointer2]);
                    expansion[pointer2 + 1] = { -1, start2, start2 + length};

                    break;
                }

                pointer++;
            }
        }

        pointer2--;
    }

    long long res = 0;

    for (long i = 0, pointer = 0; pointer < expansion.size(); pointer++) {
        long id = get<0>(expansion[pointer]);
        long start = get<1>(expansion[pointer]);
        long end = get<2>(expansion[pointer]);

        for (int j = 0; j < end - start; j++) {
            if (id != -1) {
                res += i * id;
            }

            i++;
        }
    }

    cout << "Part2: " << res << endl;
}

int main() {
    const auto in = readFile();

    part1(in);
    part2(in);
}