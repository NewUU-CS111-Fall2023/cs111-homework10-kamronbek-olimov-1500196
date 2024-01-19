#include <iostream>
#include <vector>

using namespace std;

enum State {
    Q0,  // Initial state
    Q1,  // Scan the first number
    Q2,  // Move right to find the second separator
    Q3,  // Scan the second number
    Q4,  // Move right to find the end of the tape
    Halt // Halt state
};

class Problem2 {
public:
    TuringMachine(const string& input) : tape(input), headPosition(0), currentState(Q0) {}

    void run() {
        while (currentState != Halt) {
            char currentSymbol = readSymbol();
            processSymbol(currentSymbol);
        }
    }

    void printTape() const {
        cout << tape << endl;
    }

private:
    string tape;
    int headPosition;
    State currentState;

    char readSymbol() const {
        return (headPosition < tape.size()) ? tape[headPosition] : '_';
    }

    void writeSymbol(char symbol) {
        if (headPosition < tape.size()) {
            tape[headPosition] = symbol;
        } else {
            tape += symbol;
        }
    }

    void moveHeadRight() {
        ++headPosition;
    }

    void moveHeadLeft() {
        if (headPosition > 0) {
            --headPosition;
        }
    }

    void transition(State nextState) {
        currentState = nextState;
    }

    void processSymbol(char currentSymbol) {
        switch (currentState) {
            case Q0:
                if (currentSymbol == '1') {
                    transition(Q1);
                    moveHeadRight();
                } else if (currentSymbol == '_') {
                    // Halt if tape is empty
                    transition(Halt);
                } else {
                    moveHeadRight();
                }
                break;

            case Q1:
                if (currentSymbol == '1') {
                    moveHeadRight();
                } else if (currentSymbol == '0') {
                    transition(Q2);
                    moveHeadRight();
                }
                break;

            case Q2:
                if (currentSymbol == '1') {
                    transition(Q3);
                    moveHeadRight();
                } else {
                    moveHeadRight();
                }
                break;

            case Q3:
                if (currentSymbol == '1') {
                    moveHeadRight();
                } else if (currentSymbol == '0') {
                    transition(Q4);
                    moveHeadRight();
                }
                break;

            case Q4:
                if (currentSymbol == '1') {
                    moveHeadRight();
                } else {
                    transition(Halt);
                }
                break;

            case Halt:
                // Do nothing, machine is halted
                break;
        }
    }
};

int main() {
    string input;
    cout << "Enter unary numbers separated by 0: ";
    cin >> input;

    TuringMachine tm(input);
    tm.run();

    cout << "Result: ";
    tm.printTape();

    return 0;
}
