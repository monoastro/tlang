# How do I write a program for this?
Assume the following string:
0 F R 0 F L 0
The parser interprets it as:
- 0 -> state identifier(completely useless now if I'm being completely honest)
- F R 0 -> executed if the head reads 0 from the tape
    - F -> flip the bit from 0 to 1
    - R -> move the head right
    - 0 -> transition to state 0
- F L 0 -> executed if the head reads 1 from the tape
    - F -> flip the bit from 1 to 0
    - L -> move the head left
    - 0 -> transition to state 0

The execution is assume in this order of tape operation, head operation, state transition. The programmer is expected to write their programs in this manner.
Other symbols not used here are:
- N(tape opeartion) -> no operation/don't flip the bit
- S(head operation) -> stay/don't move the head
- H(state transition) -> halt the program

Save the program as a .turing file and run it using the interpreter. Instruction below.

# Compile
Broski it's cmake, you should know how to compile with cmake.

# Run
```
bin/tlang programs/loop.turing
```
