#include <iostream>
#include <vector>

using namespace std;

bool evaluateClause(const vector<int>& clause, const vector<bool>& assignment) {
    for (int literal : clause) {
        int variable = abs(literal);
        bool isNegated = literal < 0;

        if ((assignment[variable - 1] && !isNegated) || (!assignment[variable - 1] && isNegated)) {
            // If the literal is true in the assignment, the clause is satisfied
            return true;
        }
    }
    // If no literal is true in the assignment, the clause is not satisfied
    return false;
}

bool isSatisfied(const vector<vector<int>>& cnf_formula, const vector<bool>& assignment) {
    for (const vector<int>& clause : cnf_formula) {
        if (!evaluateClause(clause, assignment)) {
            // If any clause is not satisfied, the entire formula is not satisfied
            return false;
        }
    }
    // All clauses are satisfied, so the formula is satisfied
    return true;
}

void bruteForceSAT(const vector<vector<int>>& cnf_formula, int numVariables) {
    for (int i = 0; i < (1 << numVariables); ++i) {
        // Generate all possible truth value assignments for the variables
        vector<bool> assignment;
        for (int j = 0; j < numVariables; ++j) {
            assignment.push_back((i & (1 << j)) != 0);
        }

        // Check if the current assignment satisfies the CNF formula
        if (isSatisfied(cnf_formula, assignment)) {
            // Output the satisfying assignment
            cout << "Satisfying assignment found: ";
            for (int j = 0; j < numVariables; ++j) {
                char variable = 'A' + j;
                cout << variable << " = " << (assignment[j] ? "true" : "false") << " ";
            }
            cout << endl;
            return;
        }
    }

    // If no satisfying assignment is found
    cout << "No satisfying assignment found." << endl;
}

int main() {
    // Sample CNF formula
    vector<vector<int>> cnf_formula = {{1, 2, -3}, {-1, -2, 3}, {2, -3}};
    int numVariables = 3;

    // Solve the SAT problem using brute force
    bruteForceSAT(cnf_formula, numVariables);

    return 0;
}
