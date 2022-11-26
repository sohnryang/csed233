#include <iostream>

using namespace std;

class Instruction {
public:
    void setCommand(string cmd);
    void setValue(int val);

    string getCommand();
    int getValue();

private:
    string command;
    int value;
};

class InstructionSequence {
public:
    InstructionSequence();
    ~InstructionSequence();

    int getLength();
    Instruction& getInstruction(int index);

    void parseInstructions(const char* arg);
    void printInstructions();

private:
    Instruction* instructions;
    int length;
};

const char* const TASK_1_DEFAULT_ARGUMENT="[('insertion',17), ('insertion',20), ('insertion',2), ('insertion',21), ('insertion',4), ('quickSort',NULL)]";
const char* const TASK_2_DEFAULT_ARGUMENT="[('insertion',56), ('insertion',42), ('insertion',20), ('insertion',17), ('insertion',13), ('insertion',28), ('insertion',14), ('mergeSort',NULL)]";
const char* const TASK_3_DEFAULT_ARGUMENT="[('insertion',4), ('insertion',6), ('insertion',6), ('insertion',7), ('deletion',7)]";
const char* const TASK_4_DEFAULT_ARGUMENT="[('insertion',4), ('insertion',2), ('insertion',10), ('insertion',9), ('insertion',15), ('insertion',5), ('insertion',0), ('deletion',4), ('insertion',10)]";
const char* const TASK_5_DEFAULT_ARGUMENT="[('M',4), ('insert',32615), ('insert',315), ('insert',6468), ('insert',94833)]";
const char* const TASK_6_DEFAULT_ARGUMENT="[('n',4), ('r',2), ('insert',15), ('insert',2), ('insert',3)]";

