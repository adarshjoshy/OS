#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 10
#define CI_ID 100

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

	printf("Enter Marks of 5 students:\n");
	for(int i=0; i<5; i++){
		fgets(buf[i].message, MAX, stdin);
		float marks = atof(buf[i].message);
		if((marks<0) || (marks>50)){
			printf("Please enter marks in range [0,50]\n");
			i--;
			continue;
		}

		int len = strlen(buf[i].message)+1;
		printf("In CI Process: writing marks of student %d to MQ\n", i+1);
		
		buf[i].mtype = i+1;							//for student
		if(msgsnd(msgid, &(buf[i]), len, 0) == -1){
			perror("msgsnd");
			exit(1);
		}

		buf[i].mtype = 10;                                                    	//for TA
                if(msgsnd(msgid, &(buf[i]), len, 0) == -1){
                        perror("msgsnd");
                        exit(1);
                }
	}

	//reading from TA
	struct buffer readbuf[6];
	for(int i=0; i<6; i++){
		
		if(msgrcv(msgid, &(readbuf[i]), MAX, CI_ID, 0) == -1){
                        perror("msgrcv");
                        exit(1);
                }

		if(i==0){
			printf("In CI Process: reading class average from MQ\n");
			float avg = atof(readbuf[i].message);
			printf("class average: %f\n", avg);
		}
		else{
                	printf("In CI Process: reading grade of student %d from MQ\n", i);
			printf("grade of student %d: %s\n", i, readbuf[i].message);
		}
	}

	//wait for all student to read their marks
	int count=0;
	struct buffer temp;
	while(count < 5){
		if(msgrcv(msgid, &temp, MAX, 1000, 0) == -1){
			perror("msgrcv");
			exit(1);
		}
		count++;
	}

	printf("All students have read their marks\n");

	if (msgctl(msgid, IPC_RMID, NULL) == -1) {
      		perror("msgctl");
      		exit(1);
   	}

	return 0;
}
