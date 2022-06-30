# Question 2

## Files:

- banker.c

## Instructions: 

- Compile and run program on a terminal:
	1. gcc banker.c && ./a.out
	
- Start by giving input in program banker.c

## Explanation:

- Enter number of processes(n) and number of resources(m)
- Enter AllocTable, MaxTable and total instances of each resource type
- Calculate NeedTable and Available resources
- Switch Cases:
	Press 'a' to calculate a sequence in SAFE STATE
	Press 'b' to given: sequence --> check if it is in a SAFE STATE or NOT in SAFE STATE
	Press 'c' to given: resource request --> check if request can be GRANTED or NOT GRANTED
