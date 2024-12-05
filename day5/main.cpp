#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

pair<unordered_map<int, vector<int>>, vector<vector<int>>> readFile() {
    ifstream file("../input.txt");
    string line;
    unordered_map<int, vector<int>> rules;
    vector<vector<int>> orderings;
    int key, value;
    bool flag = false;

    while (getline(file, line)) {
        if (!flag) {
            if (line.empty()) {
                flag = true;
                continue;
            }

            stringstream ss(line);
            string part;
            getline(ss, part, '|');
            key = stoi(part);

            getline(ss, part);
            value = stoi(part);

            auto it = rules.find(key);
            if (it != rules.end()) {
                it->second.push_back(value);
            } else {
                vector<int> inserted = {value};
                rules.insert({key, inserted});
            }
        } else {
            vector<int> inner;
            stringstream ss(line);
            string part;

            while (getline(ss, part, ',')) {
                inner.push_back(stoi(part));
            }

            orderings.push_back(inner);
        }
    }

    return {rules, orderings};
}

void part1(const unordered_map<int, vector<int>> &rules, const vector<vector<int>> &orderings) {
    int res = 0;

    for (const auto &order : orderings) {
        bool flag = true;

        for (int i = 0; i < order.size() && flag; i++) {
            for (int j = i + 1; j < order.size(); j++) {
                if (rules.find(order[j]) != rules.end()) {
                    vector<int> inner = rules.at(order[j]);

                    if (find(inner.begin(), inner.end(), order.at(i)) != inner.end()) {
                        flag = false;
                        break;
                    }
                }
            }
        }

        if (flag) {
            res += order.at(order.size() / 2);
        }
    }

    cout << "Part1: " << res << endl;
}

void part2(const unordered_map<int, vector<int>> &rules, vector<vector<int>> &orderings) {
    int res = 0;

    for (auto &order : orderings) {
        bool flag = false;

        for (int i = 0; i < order.size(); i++) {
            for (int j = i + 1; j < order.size(); j++) {
                if (rules.find(order[j]) != rules.end()) {
                    vector<int> inner = rules.at(order[j]);

                    if (find(inner.begin(), inner.end(), order.at(i)) != inner.end()) {
                        flag = true;
                        swap(order[i], order[j]);
                    }
                }
            }
        }

        if (flag) {
            res += order.at(order.size() / 2);
        }
    }

    cout << "Part2: " << res << endl;
}

int main() {
    auto in = readFile();

    part1(in.first, in.second);
    part2(in.first, in.second);
}
