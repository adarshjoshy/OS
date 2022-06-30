#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 10
#define TA_ID 10

struct buffer{
	long mtype;
	char message[MAX];
};

int main()
{
    	int msgid, running=5;
	int marked[5] = {0};

    	key_t key = ftok("newfile", 65);
	
	if((msgid = msgget(key, 0666 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}

	while(running){

		struct buffer student;
		int student_id;
		printf("Enter student ID: ");
		scanf("%d", &student_id);

		if((student_id < 1) || (student_id > 5)){
			printf("Please enter student ID in range [1,5]\n");
			continue;
		}

		if(marked[student_id-1]){
			printf("Student %d have read his/her marks\n", student_id);
			continue;
		}

		marked[student_id-1] = 1;
		running--;

		if(msgrcv(msgid, &(student), MAX, student_id, 0) == -1){
			perror("msgrcv");
			exit(1);
		}
		printf("In Student Process: reading marks of student %d from MQ\n", student_id);
		printf("Marks of student %d: %s", student_id, student.message);

		//notify CI Process
		sprintf(student.message, "%d", student_id);
		student.mtype = 1000;
		int len = strlen(student.message)+1;
		
		printf("In Student Process: writing read receipt to MQ\n");
		if(msgsnd(msgid, &(student), len, 0) == -1){
			perror("msgsnd");
			exit(1);
		}
	}

	printf("All students have read their marks\n");

	return 0;
}
