#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<pair<ulong, vector<ulong>>> readFile() {
    ifstream file("../input.txt");
    vector<pair<ulong, vector<ulong>>> res;
    string line;

    while (getline(file, line)) {
        string part;
        stringstream ss(line);
        ulong target;
        vector<ulong> inner;

        getline(ss, part, ':');
        target = stoul(part);

        getline(ss, part);
        stringstream values(part);
        ulong value;

        while (values >> value) {
            inner.push_back(value);
        }

        res.push_back({target, inner});
    }

    return res;
}

ulong concatenate(ulong i, ulong j) {
    string result = "";

    result += to_string(i);
    result += to_string(j);

    return stoul(result);
}

bool evaluate(const vector<ulong> &values, vector<char> operators, const ulong &target, bool isConcat) {
    if (operators.size() == values.size() - 1) { // calc the result
        ulong res = values[0];

        for (int i = 1; i < values.size(); i++) {
            if (operators[i - 1] == '*') {
                res *= values[i];
            } else if (operators[i - 1] == '+') {
                res += values[i];
            } else {
                res = concatenate(res, values[i]);
            }

            if (res > target)
                return false;
        }

        return target == res;
    } else {
        if (isConcat && values.size() > 1) {
            auto values_cpy(values);

            values_cpy[values_cpy.size() - 2] = concatenate(values_cpy[values_cpy.size() - 2], values_cpy[values_cpy.size() - 1]);
            values_cpy.pop_back();

            if (evaluate(values_cpy, operators, target, true))
                return true;
        }

        auto cpy(operators);
        bool concatRes = false;

        if (isConcat) {
            auto cpy2(operators);
            cpy2.push_back('|');

            concatRes = evaluate(values, cpy2, target, isConcat);
        }

        operators.push_back('*');
        cpy.push_back('+');

        return evaluate(values, operators, target, isConcat) || evaluate(values, cpy, target, isConcat) || concatRes;
    }
}

bool evaluatev2(const vector<ulong> &values, int i, ulong current, const ulong &target) {
    if (i >= values.size())
        return current == target;

    if (current > target) {
        return false;
    }

    return evaluatev2(values, i + 1, current * values[i], target) || evaluatev2(values, i + 1, current + values[i], target) || evaluatev2(values, i + 1, concatenate(current, values[i]), target);
}

void part1(const vector<pair<ulong, vector<ulong>>> &in) {
    ulong res = 0;

    for (auto pair : in) {
        if (evaluate(pair.second, {}, pair.first, false))
            res += pair.first;
    }

    cout << "Part1: " << res << endl;
}

void part2(const vector<pair<ulong, vector<ulong>>> &in) {
    ulong res = 0;

    for (const auto &pair : in) {
        if (evaluatev2(pair.second, 1, pair.second[0], pair.first))
            res += pair.first;
    }

    cout << "Part2: " << res << endl;
}

int main() {
    auto in = readFile();

    part1(in);
    part2(in);
}