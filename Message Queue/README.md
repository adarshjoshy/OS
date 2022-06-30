# Question 1

## Files:

- ci.c
- ta.c
- students.c

## Instructions: 

- Compile and run each program on a seperate terminal:
	1. gcc ci.c -o ci && ./ci
	2. gcc ta.c -o ta && ./ta
	3. gcc students.c -o students && ./students
	
- Start by giving input in program ci.c

## Explanation:

- Create message queue
- Enter marks in Course Instructor program (ci.c)
- Send marks to Students (ID in range [1,5]) and Teaching Assistant (ID 10)
- TA calculates class average and student grades in Teaching Assistant program (ta.c)
- Sends class average and student grades to Course Instructor (ID 100)
- Enter student ID in Students program (students.c)
- Send read receipt to Course Instructor (with message type 1000)
- Destroy message queue after all students have read their marks
