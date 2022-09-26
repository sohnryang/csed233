#include <iostream>

using namespace std;

typedef struct Instruction {
  string command;
  int value;
} Instruction;

typedef struct InstructionSequence {
  Instruction *instructions;
  int length;
} InstructionSequence;

InstructionSequence *ParseInstructions(const char *arg);
void DeleteInstructionSequence(InstructionSequence *instr_seq);
void PrintInstructionSequence(InstructionSequence *instr_seq);

const char *const TASK_3_DEFAULT_ARGUMENT =
    "[('insert',0),('insert',1),('delete',0),('insert',1),('insert',0)";
const char *const TASK_4_DEFAULT_ARGUMENT =
    "[('push',3),('top',NULL),('pop',NULL),('push',5),('top',NULL)]";
const char *const TASK_5_DEFAULT_ARGUMENT =
    "[('enqueue',5),('enqueue',3),('dequeue',NULL)]";
const char *const TASK_6_DEFAULT_ARGUMENT =
    "[('enqueue',5),('enqueue',3),('dequeue',NULL),('enqueue',6)]";