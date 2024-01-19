#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

char getVariable(int index) {
    return static_cast<char>('A' + index);
}

string generateRandom3SAT(int variables, int clauses) {
    srand(static_cast<unsigned>(time(nullptr)));

    vector<string> formula;

    for (int i = 0; i < clauses; ++i) {
        string clause;

        for (int j = 0; j < 3; ++j) {
            char variable = getVariable(rand() % variables);
            bool negate = rand() % 2 == 0;

            if (negate) {
                clause += "~";
            }

            clause += variable;

            if (j < 2) {
                clause += " | ";
            }
        }

        formula.push_back("(" + clause + ")");
    }

    string result;
    for (const string& clause : formula) {
        result += clause + " & ";
    }

    // Remove the trailing " & "
    result.erase(result.size() - 3, 3);

    return result;
}

int main() {
    // Sample input
    int variables = 3;
    int clauses = 2;

    // Generate a random 3-SAT formula
    string formula = generateRandom3SAT(variables, clauses);

    // Output the result
    cout << formula << endl;

    return 0;
}
