#include <iostream>
using namespace std;

// State Definition:
// q0: Start State. Read first digit of each number and go to state q1.
// q1: Compare digits of each number. If digits are equal, read next digits and go to state q1.
//      If first number's digit is greater, print '1' and go to state q3.
//      If second number's digit is greater, print '1 1' and go to state q3.
// q2: Move right on the tape to indicate end of comparison.
// q3: Halt State.

int main() {
    string num1, num2;
    cin >> num1 >> num2;
    int len1 = num1.length(), len2 = num2.length();

    int state = 0;
    int i = 0, j = 0;
    string tape = "101"; // To keep track of current positions of both numbers.
                          // The third symbol ('1') represents the current digit being compared.
                          // '101' indicates that both numbers are being read from the beginning.

    while (state != 3) {
        switch (state) {
            case 0: // Start State
                if (num1[i] == num2[j]) {
                    tape = "1" + num1.substr(i+1) + "1" + num2.substr(j+1);
                    state = 1;
                } else if (num1[i] > num2[j]) {
                    cout << "1 ";
                    state = 3;
                } else {
                    cout << "1 1";
                    state = 3;
                }
                break;
            case 1: // Compare digits
                if (tape[0] == '0' && tape[1] == '0') {
                    state = 3; // Both numbers are equal
                } else if (tape[0] == '0') {
                    state = 2; // Move to state q2
                } else {
                    i = num1.find(tape[0], i+1);
                    j = num2.find(tape[0], j+1);
                    state = 0; // Compare next digits
                }
                break;
            case 2: // Move right on the tape to indicate end of comparison
                tape = "110";
                state = 3; // Halt State
                break;
        }
    }
    cout << endl;
    return 0;
}
