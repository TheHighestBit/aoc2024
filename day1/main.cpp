#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<pair<int, int>> readFile() {
  ifstream file("../input.txt");

  string line;
  auto result = vector<pair<int, int>>();

  while (getline(file, line)) {
    string part1;
    string part2;
    stringstream ss(line);

    ss >> part1 >> part2;
    result.emplace_back(stoi(part1), stoi(part2));
  }

  return result;
}

void part1(const vector<pair<int, int>>& pairs) {
  vector<int> left, right;
  size_t sum = 0;

  for (const auto& [l, r] : pairs) {
    left.emplace_back(l);
    right.emplace_back(r);
  }

  ranges::sort(left);
  ranges::sort(right);

  for (int i = 0; i < left.size(); i++) {
    sum += abs(left.at(i) - right.at(i));
  }

  cout << "Part1: " << sum << endl;
}

void part2(const vector<pair<int, int>>& pairs) {
  vector<int> left, right;
  size_t sum = 0;

  for (const auto& [l, r] : pairs) {
    left.emplace_back(l);
    right.emplace_back(r);
  }

  for (size_t i : left) {
    sum += i * ranges::count(right, i);
  }

  cout << "Part2: " << sum << endl;
}

int main() {
  const auto pairs = readFile();

  part1(pairs);
  part2(pairs);
}
