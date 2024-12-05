#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

pair<unordered_map<int, int>, vector<vector<int>>> readFile() {
    ifstream file("../input.txt");
    string line;
    unordered_map<int, int> rules;
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

            rules[key] = value;
        } else {


        }
    }

}

int main() {

}
