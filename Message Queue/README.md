# Question

Consider the scenario where there are five students [ID: 1-5], a Teaching Assistant (TA) [ID: 10], and a Course Instructor (CI) [ID: 100] in a class. <br>
The CI sends the marks scored (out of 50) by the five students via a message queue so that only the particular student can read his/her marks from the message queue. <br>
However, the TA can read the marks of all the individual students also. The TA calculates the class average and assigns a grade for each student and send it back to the CI. <br>
The students cannot read the class average and their grades. <br><br>
<i>Grading: 40-50: S; 30-39: A; 20-29: B; ≤ 19: E </i>

## Files:

- ci.c
- ta.c
- students.c

## Instructions: 

- Compile and run each program on a seperate terminal:
	```
	1. gcc ci.c -o ci && ./ci
	2. gcc ta.c -o ta && ./ta
	3. gcc students.c -o students && ./students
	```
	
- Start by giving input in `program ci.c`

## Explanation:

- Create message queue
- Enter marks in Course Instructor program (ci.c)
- Send marks to Students (ID in range [1,5]) and Teaching Assistant (ID 10)
- TA calculates class average and student grades in Teaching Assistant program (ta.c)
- Sends class average and student grades to Course Instructor (ID 100)
- Enter student ID in Students program (students.c)
- Send read receipt to Course Instructor (with message type 1000)
- Destroy message queue after all students have read their marks
