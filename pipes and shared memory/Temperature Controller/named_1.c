#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<math.h>
#include<string.h>

#define F1 "/tmp/f1"
#define F2 "/tmp/f2"
#define F3 "/tmp/f3"

int main(){
	int fd1, fd3;

	float L[5];
	int category[5];

	mkfifo(F1, 0666);
	
	fd1 = open(F1, O_WRONLY);

start:
        printf("Enter temperature of 5 locations (L) :\n");
        for(int i=0; i<5; i++) scanf("%f", &L[i]);

        for(int i=0; i<5; i++){
                if(L[i] < 15 || L[i] > 45){
                        printf("Values entered are not in range 15 deg Celsius to 45 deg Celsius\n");
                        memset(L, 0, sizeof(L));
                        goto start;
                }
        }

	printf("In Process 1: writing L values to f1\n");
        write(fd1, L, sizeof(L));
	close(fd1);

	fd3 = open(F3, O_RDONLY);

        read(fd3, category, sizeof(category));
        printf("In Process 1: reading categories from f3\n");
	close(fd3);

        for(int i=0; i<5; i++){
                if(category[i] == 1) L[i] -= 3;
                else if(category[i] == 2) L[i] -= 1.5;
                else if(category[i] == 3) L[i] += 2;
                else if(category[i] == 4) L[i] += 2.5;
        }

        for(int i=0; i<5; i++)
                printf("Temperature at L%d: %f\n", i+1, L[i]);

	unlink(F1);
	unlink(F2);
	unlink(F3);

	return  0;
}
