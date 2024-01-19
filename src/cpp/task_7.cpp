#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int minRabbits(vector<int>& answers) {
    unordered_map<int, int> count;

    for (int ans : answers) {
        count[ans]++;
    }

    int result = 0;

    for (auto& entry : count) {
        int groupSize = entry.first + 1;
        int rabbitsInGroup = entry.second;

        // Calculate the number of groups needed for the current color
        result += (rabbitsInGroup + groupSize - 1) / groupSize * groupSize;
    }

    return result;
}

int main() {
    // Sample input
    vector<int> answers = {1, 1, 2};

    // Calculate the minimum number of rabbits
    int result = minRabbits(answers);

    // Output the result
    cout << "Minimum number of rabbits: " << result << endl;

    return 0;
}
