#include <iostream>
#include <vector>

using namespace std;

enum State {
    Q0,  // Initial state, ignore 0's and separator (c), move right
    Q1,  // Convert B to C and move left
    Q2,  // Ignore 0's and move left
    Q3,  // Convert C to C and move right
    Q4,  // Convert X to X and move right, handle 0 or C
    Q5,  // Convert X to X and move left, handle C or Y
    Q6,  // Convert B to B and move right, handle Y or C
    Q7,  // Handle transitions after Y or 0 in step 5
    Q8,  // Handle transitions after Y in step 6
    Halt // Halt state
};

class Problem4 {
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
                if (currentSymbol == '0' || currentSymbol == 'c') {
                    moveHeadRight();
                } else if (currentSymbol == 'B') {
                    transition(Q1);
                    moveHeadLeft();
                } else {
                    // Halt if unexpected symbol is encountered
                    transition(Halt);
                }
                break;

            case Q1:
                if (currentSymbol == 'B') {
                    moveHeadLeft();
                } else {
                    transition(Q2);
                    moveHeadLeft();
                }
                break;

            case Q2:
                if (currentSymbol == '0') {
                    moveHeadLeft();
                } else {
                    transition(Q3);
                    moveHeadRight();
                }
                break;

            case Q3:
                if (currentSymbol == 'X') {
                    moveHeadRight();
                } else {
                    transition(Q4);
                    moveHeadRight();
                }
                break;

            case Q4:
                if (currentSymbol == '0') {
                    writeSymbol('X');
                    moveHeadLeft();
                } else if (currentSymbol == 'C') {
                    writeSymbol('B');
                    transition(Q7);
                    moveHeadRight();
                } else {
                    transition(Halt);
                }
                break;

            case Q5:
                if (currentSymbol == 'B') {
                    moveHeadRight();
                } else if (currentSymbol == 'C') {
                    transition(Q6);
                    moveHeadLeft();
                } else {
                    transition(Halt);
                }
                break;

            case Q6:
                if (currentSymbol == 'Y') {
                    moveHeadLeft();
                } else if (currentSymbol == 'C') {
                    moveHeadLeft();
                } else {
                    transition(Q5);
                    moveHeadLeft();
                }
                break;

            case Q7:
                if (currentSymbol == 'Y') {
                    writeSymbol('0');
                    moveHeadRight();
                } else if (currentSymbol == 'C') {
                    moveHeadRight();
                } else if (currentSymbol == '0') {
                    transition(Q8);
                    moveHeadRight();
                } else {
                    transition(Halt);
                }
                break;

            case Q8:
                if (currentSymbol == 'Y') {
                    writeSymbol('Y');
                    moveHeadRight();
                } else if (currentSymbol == 'C') {
                    transition(Q7);
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
    // Example input: "0c1111c111" represents unary 6 multiplied by unary 3
    string input;
    cout << "Enter unary numbers separated by c and prefixed by 0: ";
    cin >> input;

    TuringMachine tm(input);
    tm.run();

    cout << "Multiplication result: ";
    tm.printTape();

    return 0;
}
