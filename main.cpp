#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

// Structure for representing a state machine
struct FiniteAutomaton {
    set<int> states;  // set states
    int initial_state; // initial state
    set<int> final_states; // set final states
    map<pair<int, char>, int> transitions; // Transition function (state, symbol) -> next state
};

// Function to check if the machine accepts the word w
bool acceptsWord(const FiniteAutomaton& automaton, const string& w) {
    int current_state = automaton.initial_state;

    // Process w
    for (char c : w) {
        auto transition = automaton.transitions.find({ current_state, c });
        if (transition == automaton.transitions.end()) {
            return false; // No transition for character c
        }
        current_state = transition->second;
    }

    return automaton.final_states.count(current_state) > 0; // Checking the final state
}

int main() {
    setlocale(LC_ALL, "Russian");
    FiniteAutomaton automaton;

    // Fixed word "w0" here
    string w0 = "for";

    // Read data about the state machine from a file
    ifstream input("automaton.txt");
    if (!input.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }

    // Read ||A|| alphabet
    int alphabet_size;
    input >> alphabet_size;

    // Read ||S||
    int num_states;
    input >> num_states;

    // Read the initial state s0
    input >> automaton.initial_state;

    // Read ||F|| and final states
    int num_final_states;
    input >> num_final_states;
    for (int i = 0; i < num_final_states; i++) {
        int final_state;
        input >> final_state;
        automaton.final_states.insert(final_state);
    }

    // Read the transition function
    int s, s_next;
    char a;
    while (input >> s >> a >> s_next) {
        automaton.transitions[{s, a}] = s_next;
    }

    input.close();

    // Prompt the user to enter the word "w1"
    cout << "Введите слово w1: ";
    string w1;
    cin >> w1;

    // Checking the word "w0 + w1"
    string w = w0 + w1;
    bool result = acceptsWord(automaton, w);

    if (result) {
        cout << "Конечный автомат допускает слово w = " << w << endl;
    }
    else {
        cout << "Конечный автомат не допускает слово w = " << w << endl;
    }

    return 0;
}
