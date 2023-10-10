#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <string>

struct Automaton {
    std::set<char> A; // �������
    std::set<int> S;  // ���������
    int s0;  // ��������� ���������
    std::set<int> F;  // ��������� ���������
    std::map<std::pair<int, char>, int> f;  // ������� ���������
};

std::string findWordW1(const Automaton& automaton, const std::string& w0) {
    // ���������� ��� ��������� S � ���������, ����� �� �� ��� ������� � ��������� ���������,
    // �������� ����� w0.
    for (int state : automaton.S) {
        int current_state = state;
        bool is_accepted = true;
        std::string w1;

        for (char symbol : w0) {
            auto it = automaton.f.find({ current_state, symbol });
            if (it == automaton.f.end()) {
                // �������� ���
                is_accepted = false;
                break;
            }
            else {
                // ��������� � ��������� ���������
                current_state = it->second;
                w1.push_back(symbol);
            }
        }

        // ���������, �������� �� ������� ��������� ���������
        if (is_accepted && automaton.F.count(current_state)) {
            return w1;
        }
    }
    return ""; // ���������� ������ ������, ���� ����� �� �������
}

bool readAutomaton(const std::string& filename, Automaton& automaton) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        return false;
    }

    int size;
    char a;

    // ��������� �������
    infile >> size;
    for (int i = 0; i < size; i++) {
        infile >> a;
        automaton.A.insert(a);
    }

    // ��������� ���������
    infile >> size;
    for (int i = 0; i < size; i++) {
        automaton.S.insert(i);
    }

    // ��������� ��������� ���������
    infile >> automaton.s0;

    // ��������� ��������� ���������
    infile >> size;
    int fs;
    for (int i = 0; i < size; i++) {
        infile >> fs;
        automaton.F.insert(fs);
    }

    // ��������� ������� ���������
    int s, s_prime;
    while (infile >> s >> a >> s_prime) {
        automaton.f[{s, a}] = s_prime;
    }

    infile.close();
    return true;
}


bool isWordAccepted(const Automaton& automaton, const std::string& w0) {
    return !findWordW1(automaton, w0).empty();
}


int main() {
    Automaton automaton;
    if (!readAutomaton("automaton.txt", automaton)) {
        std::cerr << "Failed to read automaton" << std::endl;
        return 1;
    }

    std::string w0;
    char continueAnswer;

    do {
        std::cout << "Enter word w0: ";
        std::cin >> w0;

        std::string w1 = findWordW1(automaton, w0);
        if (!w1.empty()) {
            std::cout << "There exists a word w1 = " << w1 << " such that w = w1w0 is accepted by the automaton" << std::endl;
        }
        else {
            std::cout << "No such word w1 exists that w = w1w0 is accepted by the automaton" << std::endl;
        }

        std::cout << "Do you want to check another word? (y/n): ";
        std::cin >> continueAnswer;

    } while (continueAnswer == 'y' || continueAnswer == 'Y');

    return 0;
}


