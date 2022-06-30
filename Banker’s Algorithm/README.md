# Question:

Design and implement the Banker’s algorithm. <br>
The algorithm should receive as input the AllocTable, MaxTable, and the total number of instances per resource type.
- The program should output the sequence of process that is SAFE STATE.
- Given the set of sequence of processes, the program should output whether the given sequence is in a SAFE STATE or not.
- Given the resource request of a process, the program should check whether the request can be granted or not.

## Files:

- banker.c

## Instructions: 

- Compile and run program on a terminal:
```
	1. gcc banker.c && ./a.out
```
	
- Start by giving input in program `banker.c`

## Explanation:

- Enter number of processes(n) and number of resources(m)
- Enter AllocTable, MaxTable and total instances of each resource type
- Calculate NeedTable and Available resources
- Switch Cases:
	- Press 'a' to calculate a sequence in SAFE STATE
	- Press 'b' to check if given sequence is in a SAFE STATE or NOT in SAFE STATE
	- Press 'c' to check if given resource request request can be GRANTED or NOT GRANTED
