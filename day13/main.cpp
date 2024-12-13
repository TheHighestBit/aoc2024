#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Machine {
    int xa, xb;       // Button A and Button B X offsets
    int ya, yb;       // Button A and Button B Y offsets
    long long targetx, targety; // Prize coordinates
};

// ChatGPT generated cause ICBA
vector<Machine> readFile() {
    std::ifstream file("../input.txt");
    std::vector<Machine> machines;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << std::endl;
        return machines;
    }

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        Machine m;

        // -------------------
        // Parse Button A line
        // Expected format: "Button A: X+94, Y+34"
        // -------------------
        // Extract X+ value
        size_t xa_pos = line.find("X+");
        if (xa_pos != std::string::npos) {
            size_t comma_pos = line.find(',', xa_pos);
            if (comma_pos != std::string::npos) {
                std::string xa_str = line.substr(xa_pos + 2, comma_pos - (xa_pos + 2));
                m.xa = std::stoi(xa_str);
            }
        }

        // Extract Y+ value
        size_t ya_pos = line.find("Y+");
        if (ya_pos != std::string::npos) {
            std::string ya_str = line.substr(ya_pos + 2);
            m.ya = std::stoi(ya_str);
        }

        // -------------------
        // Parse Button B line
        // Read the next line for Button B
        // Expected format: "Button B: X+22, Y+67"
        // -------------------
        if (!std::getline(file, line)) break; // Ensure there is a next line

        // Extract X+ value
        size_t xb_pos = line.find("X+");
        if (xb_pos != std::string::npos) {
            size_t comma_pos = line.find(',', xb_pos);
            if (comma_pos != std::string::npos) {
                std::string xb_str = line.substr(xb_pos + 2, comma_pos - (xb_pos + 2));
                m.xb = std::stoi(xb_str);
            }
        }

        // Extract Y+ value
        size_t yb_pos = line.find("Y+");
        if (yb_pos != std::string::npos) {
            std::string yb_str = line.substr(yb_pos + 2);
            m.yb = std::stoi(yb_str);
        }

        // -------------------
        // Parse Prize line
        // Read the next line for Prize
        // Expected format: "Prize: X=8400, Y=5400"
        // -------------------
        if (!std::getline(file, line)) break; // Ensure there is a next line

        // Extract X= value
        size_t targetx_pos = line.find("X=");
        if (targetx_pos != std::string::npos) {
            size_t comma_pos = line.find(',', targetx_pos);
            if (comma_pos != std::string::npos) {
                std::string targetx_str = line.substr(targetx_pos + 2, comma_pos - (targetx_pos + 2));
                m.targetx = std::stoi(targetx_str);
            }
        }

        // Extract Y= value
        size_t targety_pos = line.find("Y=");
        if (targety_pos != std::string::npos) {
            std::string targety_str = line.substr(targety_pos + 2);
            m.targety = std::stoi(targety_str);
        }

        // Add the parsed Machine to the vector
        machines.push_back(m);
    }

    file.close();
    return machines;
}

long long solveMachine(const Machine& machine) {
    // Need to solve this system of equations but prefer pressing b:
    // m * xa + n * xb = targetx
    // m * ya + n * yb = targety

    long long max_n = machine.targetx / machine.xb; // Prefer b button
    for (long long n = 0; n <= max_n; ++n) {
        long long remaining_x = machine.targetx - machine.xb * n;

        // Check if remaining_x is divisible by xa
        if (machine.xa == 0) {
            if (remaining_x != 0) continue;
        } else {
            if (remaining_x < 0) continue;
            if (remaining_x % machine.xa != 0) continue;
        }

        long long m = (machine.xa != 0) ? remaining_x / machine.xa : 0;

        // Now check if this m also satisfies the Y equation
        long long calculated_y = machine.ya * m + machine.yb * n;
        if (calculated_y == machine.targety) {
            return n + 3 * m;
        }
    }

    if (machine.targetx % machine.xb == 0) {
        long long n = machine.targetx / machine.xb;
        if (machine.yb * n == machine.targety) return n;
    }

    if (machine.targetx % machine.xa == 0) {
        long long m = machine.targetx / machine.xa;
        if (machine.ya * m == machine.targety) return m * 3;
    }

    return -1;
}

void part1(const vector<Machine>& machines) {
    int res = 0;

    for (const auto& machine : machines) {
        int inner = solveMachine(machine);
        if (inner != -1) {
            res += inner;
        }
    }

    cout << "Part1: " << res << endl;
}

void part2(vector<Machine>& machines) {
    for (auto& machine : machines) {
        machine.targetx += 10000000000000;
        machine.targety += 10000000000000;
    }

    long long res = 0;

    for (const auto& machine : machines) {
        long long inner = solveMachine(machine);
        if (inner != -1) {
            res += inner;
        }
    }

    cout << "Part2: " << res << endl;
}

int main() {
    auto machines = readFile();

    part1(machines);
    part2(machines);
}