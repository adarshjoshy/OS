# Password strength calculator using shared memory

## Files:

- shm_1.c
- shm_2.c
- shm_3.c

## Instructions:

- Compile and run each process on a seperate terminal:
```
	1. gcc shm_1.c -o p1 && ./p1
	2. gcc shm_2.c -o p2 && ./p2
	3. gcc shm_2.c -o p3 && ./p3
```	
- Start by giving input in `process p1`.

## Processes:

- Process 1:
  1. Create and attatch shared memory.
  2. Read password from stdin.
  3. Block the process till the data is received from process 3.
  4. Read strength values and print corresponding message.
  5. Detatch and destroy shared memory.

- Process 2:
  1. Attatch shared memory.
  2. Block the process till the data is received from process 1.
  2. Calculate the number of alphanumeric and special characters.
  3. Write the values to shared memory.
  4. Detatch shared memory.
  
- Process 3:
  1. Attatch shared memory.
  2. Block the process till the data is received from process 2.
  2. Decide password strength based on the given rule.
  3. Write the value to shared memory.
  4. Detatch shared memory.
  
## Shared memory segmentation:

Shared memory is segmented with the help of struct.

```
	struct shmseg{
		char password[20];
		int alphanum;
		int special;
		int strength;
	};
```
