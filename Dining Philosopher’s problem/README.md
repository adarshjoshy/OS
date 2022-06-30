# Question 3

## Files:

- dpp.c

## Instructions: 

- Compile and run program on a terminal:
	1. gcc -pthread dpp.c && ./a.out

## Explanation:

- N semaphores(s[0], s[1], ...s[N-1]) are initialized to 0
- Philosophers(P) can be in 3 states: 
	1. THINKING
	2. HUNGRY
	3. EATING
- A Philosopher(P) can EAT only if neighbors do not EAT
- A Philosopher(P) in HUNGRY state are waiting for neighbors to finish EATING
- Other Philosophers(P) are in THINKING state
