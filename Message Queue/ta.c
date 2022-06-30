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
    	struct buffer buf[5];

    	int msgid;
  
    	key_t key = ftok("newfile", 65);

	if((msgid = msgget(key, 0666 | IPC_CREAT)) == -1){
		perror("msgget");
		exit(1);
	}

	for(int i=0; i<5; i++){

		if(msgrcv(msgid, &(buf[i]), MAX, TA_ID, 0) == -1){
			perror("msgrcv");
			exit(1);
		}
		printf("In TA Process: reading marks of student %d from MQ\n", i+1);
	}

	struct buffer buf_ta[6];

	//calculate class average
	float avg;
	for(int i=0; i<5; i++){
		avg += atof(buf[i].message);
	}
	avg /= 5;
	printf("class average: %f\n", avg);
	
 	gcvt(avg, 5, buf_ta[0].message);				//convert float to string

	buf_ta[0].mtype = 100;
	int len = strlen(buf_ta[0].message)+1;
	printf("In TA Process: writing class average to MQ\n");
	if(msgsnd(msgid, &(buf_ta[0]), len, 0) == -1){
		perror("msgsnd");
		exit(1);
	}

	//calculate grades
	for(int i=1; i<6; i++){
		char* grade;
		float marks = atof(buf[i-1].message);
		if(marks>=40 && marks<=50) grade = "S";
		else if(marks>=30 && marks<40) grade = "A";
		else if(marks>=20 && marks<30) grade = "B";
		else grade = "E";
		printf("grade of student %d: %s\n", i, grade);

		strcpy(buf_ta[i].message, grade);
		buf_ta[i].mtype = 100;
		len = strlen(buf_ta[i].message)+1;
		
		printf("In TA Process: writing grade of student %d to MQ\n", i);
		if(msgsnd(msgid, &(buf_ta[i]), len, 0) == -1){
			perror("msgsnd");
			exit(1);
		}
	}

	return 0;
}
