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


InstructionSequence* ParseInstructions(const char* arg) {
    string str(arg);
    int cnt = 0;
    int instr_num;

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
                    instr_array[cnt].command = buffer;
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
                        instr_array[cnt].value = stoi(buffer);
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

    InstructionSequence* instr_seq = new InstructionSequence;
    instr_seq->instructions = instr_array;
    instr_seq->length = instr_num;

    return instr_seq;
}


void DeleteInstructionSequence(InstructionSequence* instr_seq) {
    delete[] instr_seq->instructions;
    delete instr_seq;
}


void PrintInstructionSequence(InstructionSequence* instr_seq) {
    cout << "Length = " << instr_seq->length << endl;
    for (int i = 0; i < instr_seq->length; i++) {
        cout << "Element " << i << endl;
        cout << "  command: " << instr_seq->instructions[i].command << endl;
        cout << "  value  : " << instr_seq->instructions[i].value << endl;
    }
}
    