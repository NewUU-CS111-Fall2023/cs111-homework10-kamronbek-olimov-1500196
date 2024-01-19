#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool evaluateClause(const vector<int>& clause, const unordered_set<int>& assignment) {
    for (int literal : clause) {
        if (assignment.count(literal) > 0) {
            // If the literal is true in the assignment, the clause is satisfied
            return true;
        }
    }
    // If no literal is true in the assignment, the clause is not satisfied
    return false;
}

bool isSatisfied(vector<vector<int>>& cnf, unordered_set<int>& assignment) {
    for (const vector<int>& clause : cnf) {
        if (!evaluateClause(clause, assignment)) {
            // If any clause is not satisfied, the entire formula is not satisfied
            return false;
        }
    }
    // All clauses are satisfied, so the formula is satisfied
    return true;
}

int main() {
    // Sample CNF formula: (x1 OR x2) AND (NOT x1 OR x3 OR x4)
    vector<vector<int>> cnf = {{1, 2}, {-1, 3, 4}};

    // Sample truth value assignment: {x1=true, x2=false, x3=true, x4=true}
    unordered_set<int> assignment = {1, -2, 3, 4};

    // Check if the formula is satisfied by the assignment
    bool result = isSatisfied(cnf, assignment);

    // Output the result
    cout << (result ? "True" : "False") << endl;

    return 0;
}
