# Temperature Controller using unnamed pipe

## Files:

- unnamed.c

## Instructions: 

- Compile and run the program : gcc unnamed.c -lm && ./a.out

## Processes:

- Create the 3 pipes using pipe()
- Close the reading end (0) before writing and
  Close the writing end (1) before reading at the start of each process.

- Parent Process: 
  1. Take temperature input from stdin.
  2. Write temperature values to pipe 1.
  3. Read categories returned from child process 2 through pipe 3.
  4. Update temperature values as per the rule and print.
  
- Child Process 1:
  1. Read temperature values from pipe 1.
  2. Calculate average and standard deviation.
  3. Write temperature values, average and standard deviation to pipe 2.
  
- Child Process 2:
  1. Read temperature values, average and standard deviation from pipe 2.
  2. Categorize temperature values as per the rule.
  3. Write categories to pipe 3.
  
  
# Temperature Controller using named pipe

## Files:

- named_1.c
- named_2.c
- named_3.c

## Instructions:

- Compile and run each process on a seperate terminal:
	1. gcc named_1.c -o p1 && ./p1
	2. gcc named_2.c -lm -o p2 && ./p2
	3. gcc named_2.c -o p3 && ./p3
	
- Start by giving input in process p1.

## Processes:

- Open before and close after reading/writing in named pipe.

- Process 1:
  1. Create named pipe 'f1'.
  2. Take temperature input from stdin.
  3. Write temperature values to named pipe 'f1'.
  4. Read categories returned from process 3 through named pipe 'f3'.
  5. Update temperature values as per the rule and print.
  6. Unlink all named pipes.

- Process 2:
  1. Create named pipe 'f2'.
  2. Read temperature values from named pipe 'f1'.
  3. Calculate average and standard deviation.
  4. Write temperature values, average and standard deviation to named pipe 'f2'.
  
- Process 3:
  1. Create named pipe 'f3'.
  2. Read temperature values, average and standard deviation from named pipe 'f2'.
  3. Categorize temperature values as per the rule.
  4. Write categories to named pipe 'f3'.
