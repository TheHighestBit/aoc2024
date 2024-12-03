#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<char> readFile() {
    ifstream file("../input.txt");
    char single;
    vector<char> res;

    while (file.get(single)) {
        res.emplace_back(single);
    }

    return res;
}

int charstoi(const std::vector<char>& number) {
    int res = 0;

    for (const char c : number) {
        res = res * 10 + (c - '0');
    }

    return res;
}

void part1(const vector<char>& instructions) {
    int res = 0;
    vector<char> arg1, arg2, stack;
    bool flag1 = false;
    bool flag2 = false;

    for (char instruction : instructions) {
        if (stack.empty() && instruction == 'm' || stack.size() == 1 && instruction == 'u' || stack.size() == 2 && instruction == 'l') {
            stack.emplace_back(instruction);
        } else if (stack.size() == 3 && instruction == '(' && !flag1) {
            stack.emplace_back('(');
            flag1 = true;
        } else if (stack.size() == 4 && flag1 && !arg1.empty() && instruction == ',') {
            stack.emplace_back(',');
            flag1 = false;
            flag2 = true;
        } else if (stack.size() == 5 && !flag1 && flag2 && instruction == ')') {
            res += charstoi(arg1) * charstoi(arg2);
            stack.clear();
            arg1.clear();
            arg2.clear();
            flag1 = false;
            flag2 = false;
        } else if (isdigit(instruction) && (flag1 || flag2)) {
            if (flag1) {
                arg1.emplace_back(instruction);
            } else if (flag2) {
                arg2.emplace_back(instruction);
            }
        } else {
            stack.clear();
            arg1.clear();
            arg2.clear();
            flag1 = false;
            flag2 = false;
        }
    }

    cout << "Part1: " << res << endl;
}

void part2(const vector<char>& instructions) {
    int res = 0;
    vector<char> arg1, arg2, stack, control;
    bool flag1 = false;
    bool flag2 = false;
    bool isEnabled = true;

    for (char instruction : instructions) {
        if (control.empty() && instruction == 'd' || control.size() == 1 && instruction == 'o' || control.size() == 2 && (instruction == 'n' || instruction == '(') || control.size() == 3 && instruction == '\'' || control.size() == 4 && instruction == 't' || control.size() == 5 && instruction == '(') {
            control.emplace_back(instruction);
        } else if (instruction == ')') {
            if (control.size() == 3) {
                isEnabled = true;
            } else if (control.size() == 6) {
                isEnabled = false;
            }

            control.clear();
        } else {
            control.clear();
        }

        if (isEnabled && (stack.empty() && instruction == 'm' || stack.size() == 1 && instruction == 'u' || stack.size() == 2 && instruction == 'l')) {
            stack.emplace_back(instruction);
        } else if (stack.size() == 3 && instruction == '(' && !flag1) {
            stack.emplace_back('(');
            flag1 = true;
        } else if (stack.size() == 4 && flag1 && !arg1.empty() && instruction == ',') {
            stack.emplace_back(',');
            flag1 = false;
            flag2 = true;
        } else if (stack.size() == 5 && !flag1 && flag2 && instruction == ')') {
            res += charstoi(arg1) * charstoi(arg2);
            stack.clear();
            arg1.clear();
            arg2.clear();
            flag1 = false;
            flag2 = false;
        } else if (isdigit(instruction) && (flag1 || flag2)) {
            if (flag1) {
                arg1.emplace_back(instruction);
            } else if (flag2) {
                arg2.emplace_back(instruction);
            }
        } else {
            stack.clear();
            arg1.clear();
            arg2.clear();
            flag1 = false;
            flag2 = false;
        }
    }

    cout << "Part2: " << res << endl;
}

int main() {
    auto const instructions = readFile();

    part1(instructions);
    part2(instructions);
}