#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<math.h>

#define F1 "/tmp/f1"
#define F2 "/tmp/f2"
#define F3 "/tmp/f3"

int main(){
	int fd2, fd3;

	float L[5], message[7];
	int cat[5];

	mkfifo(F3, 0666);

	fd2 = open(F2, O_RDONLY);
		
	read(fd2, message, sizeof(message));
        printf("In Process 3: reading L values, mean & std dev from f2\n");
	close(fd2);

        for(int i=0; i<5; i++) L[i] = message[i];
       	float mean = message[5];
       	float sd   = message[6];

	for(int i=0; i<5; i++){
        	if(L[i] == mean) cat[i] = 0;
                else if(L[i] > mean + sd) cat[i] = 1;
                else if(L[i] > mean && L[i] < mean + sd) cat[i] = 2;
                else if(L[i] < mean && L[i] > mean - sd) cat[i] = 3;
                else cat[i] = 4;
      	}

        for(int i=0; i<5; i++)
        	printf("Category of L%d: %d\n", i+1, cat[i]);

	fd3 = open(F3, O_WRONLY);

	printf("In Process 3: writing categories to f3\n");
        write(fd3, cat, sizeof(cat));
	close(fd3);

	return  0;
}
