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
	int fd1, fd2;

	float L[5], message[7];

	mkfifo(F2, 0666);

	fd1 = open(F1, O_RDONLY);
		
	read(fd1, L, sizeof(L));
        printf("In Process 2: reading L values from f1\n");
	close(fd1);

	// calculate mean
        float mean = 0;
      	for(int i=0; i<5; i++) mean += L[i];
        mean /= 5;

        // calculate standard deviation
      	float sd = 0;
      	for(int i=0; i<5; i++)
        	sd += pow((L[i] - mean), 2);

     	sd /= 5;
      	sd = sqrtf(sd);

        printf("mean: %f std_dev: %f\n", mean, sd);

     	for(int i=0; i<5; i++) message[i] = L[i];
     	message[5] = mean;
     	message[6] = sd;

	fd2 = open(F2, O_WRONLY);

     	printf("In Process 2: writing L values, mean & std dev to f2\n");
	write(fd2, message, sizeof(message));
	close(fd2);

	return  0;
}
