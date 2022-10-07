#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

// States for instruction parsing
enum State {
    STATE_START,
    STATE_START_INSTR,
    STATE_START_COMMAND,
    STATE_IN_QUOTE,
    STATE_END_COMMAND,
    STATE_VALUE,
    STATE_END_INSTR,
    STATE_END,
};


/* Member functions for Instruction class */
void Instruction::setCommand(string cmd) {
    this->command = cmd;
}

void Instruction::setValue(int val) {
    this->value = val;
}

string Instruction::getCommand() {
    return this->command;
}

int Instruction::getValue() {
    return this->value;
}


/* Member functions for InstructionSequence class */
InstructionSequence::InstructionSequence() {
    this->instructions = NULL;
}

InstructionSequence::~InstructionSequence() {
    if (this->instructions != NULL)
        delete[] this->instructions;
}

int InstructionSequence::getLength() {
    return this->length;
}

Instruction& InstructionSequence::getInstruction(int index) {
    return this->instructions[index];
}

void InstructionSequence::parseInstructions(const char* arg) {
    string str(arg);
    int cnt = 0;
    int instr_num;

    if (this->instructions != NULL)
        delete[] this->instructions;

    // Count comma (,) to approximate the number of instructions
    for (int i = 0; i < str.length(); i++)
        if (str[i] == ',')
            cnt += 1;
    instr_num = (cnt + 1) / 2;  // Number of Instructions


    Instruction* instr_array = new Instruction[instr_num];
    State state = STATE_START;
    string buffer = "";
    char quote = ' ';
    char curr;

    // Parse an input argument to instructions
    cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        curr = str[i];

        // Ignore whitespace
        if (curr == ' ')
            continue;

        switch(state) {
            case STATE_START:
                if (curr == '[') {
                    state = STATE_START_INSTR;
                } else {
                    throw "Invalid instructions";
                }
                break;
            case STATE_START_INSTR:
                if (curr == '(') {
                    state = STATE_START_COMMAND;
                } else if (curr == ']' && instr_num == 0) {
                    state = STATE_END;
                } else {
                    throw "Invalid instructions";
                }
                break;
            case STATE_START_COMMAND:
                if (curr == '\'' || curr == '"') {
                    quote = curr;
                    state = STATE_IN_QUOTE;
                } else {
                    throw "Invalid instructions";
                }
                break;
            case STATE_IN_QUOTE:
                if (curr == quote) {
                    instr_array[cnt].setCommand(buffer);
                    buffer = "";
                    quote = ' ';
                    state = STATE_END_COMMAND;
                } else {
                    buffer += curr;
                }
                break;
            case STATE_END_COMMAND:
                if (curr == ',') {
                    state = STATE_VALUE;
                } else {
                    throw "Invalid instructions";
                }
                break;
            case STATE_VALUE:
                if (curr == ')') {
                    if (buffer.compare("NULL") != 0)
                        instr_array[cnt].setValue(stoi(buffer));
                    buffer = "";
                    state = STATE_END_INSTR;
                } else {
                    buffer += curr;
                }
                break;
            case STATE_END_INSTR:
                if (curr == ',') {
                    cnt += 1;
                    state = STATE_START_INSTR;
                } else if (curr == ']') {
                    state = STATE_END;
                } else {
                    throw "Invalid instructions";
                }
                break;
            default:
                throw "Invalid instructions";
        }
    }

    this->instructions = instr_array;
    this->length = instr_num;
}

void InstructionSequence::printInstructions() {
    cout << "Length = " << this->length << endl;
    for (int i = 0; i < this->length; i++) {
        cout << "Element " << i << endl;
        cout << "  command: " << this->instructions[i].getCommand() << endl;
        cout << "  value  : " << this->instructions[i].getValue() << endl;
    }
}
