#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<string.h>

int main()
{
	int fd1[2], fd2[2], fd3[2];
	int status1, status2, status3;
	int pid1, pid2;

	float L[5];
	int category[5];

	status1 = pipe(fd1);
	if(status1 == -1){
		printf("Pipe 1 failed\n");
		return 1;
	}

	status2 = pipe(fd2);
	if(status2 == -1){
		printf("Pipe 2 failed\n");
		return 1;
	}

	status3 = pipe(fd3);
	if(status3 == -1){
		printf("Pipe 3 failed\n");
		return 1;
	}

	pid1 = fork();

	if(pid1 != 0){					// parent process
		close(fd1[0]);
		close(fd3[1]);
		
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

		printf("In Parent: writing L values to pipe 1\n");
		write(fd1[1], L, sizeof(L));

		read(fd3[0], category, sizeof(category));
		printf("In Parent: reading categories from pipe 3\n");

		for(int i=0; i<5; i++){
			if(category[i] == 1) L[i] -= 3;
			else if(category[i] == 2) L[i] -= 1.5;
			else if(category[i] == 3) L[i] += 2;
			else if(category[i] == 4) L[i] += 2.5;
		}

		for(int i=0; i<5; i++)
			printf("Temperature at L%d: %f\n", i+1, L[i]);
		
	}
	else{						// child process 1

		close(fd1[1]);

		float L1[5], message1[7];

		read(fd1[0], L1, sizeof(L1));
		printf("In Child 1: reading L values from pipe 1\n");

		// calculate mean
		float mean = 0;
		for(int i=0; i<5; i++) mean += L1[i];
		mean /= 5;

		// calculate standard deviation
		float sd = 0;
	       	for(int i=0; i<5; i++)
            		sd += pow((L1[i] - mean), 2);

        	sd /= 5;
        	sd = sqrtf(sd);

        	printf("mean: %f std_dev: %f\n", mean, sd);

		for(int i=0; i<5; i++) message1[i] = L1[i];
		message1[5] = mean;
		message1[6] = sd;
		
		printf("In Child 1: writing L values, mean & std dev to pipe 2\n");
		write(fd2[1], message1, sizeof(message1));
		
		pid2 = fork();

		if(pid2 == 0){				// child process 2
			close(fd2[1]);
			close(fd3[0]);

			float L2[5], message2[7];
			int cat[5];

			read(fd2[0], message2, sizeof(message2));
			printf("In Child 2: reading L values, mean & std dev from pipe 2\n");

			for(int i=0; i<5; i++) L2[i] = message2[i];
			float mean_ = message2[5];
			float sd_   = message2[6];
			
			for(int i=0; i<5; i++){
				if(L2[i] == mean_) cat[i] = 0;
				else if(L2[i] > mean_ + sd_) cat[i] = 1;
				else if(L2[i] > mean_ && L2[i] < mean_ + sd_) cat[i] = 2;
				else if(L2[i] < mean_ && L2[i] > mean_ - sd_) cat[i] = 3;
				else cat[i] = 4;
			}

			for(int i=0; i<5; i++)
				printf("Category of L%d: %d\n", i+1, cat[i]);

			printf("In Child 2: writing categories to pipe 3\n");
			write(fd3[1], cat, sizeof(cat));	
		}	

	}
	
	return 0;
}
