#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>

struct shmseg{
	char password[20];
	int alphanum;
	int special;
	int strength;
};

int main(){
	struct shmseg *shmp;
	
	key_t key = ftok("shmfile", 65);
	
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
	if(shmid == -1){
		printf("Shared memory allocation failed\n");
		return 1;
	}

	shmp = shmat(shmid, NULL, 0);
	if(shmp == (void*) -1){
		printf("Shared memory attach failed\n");
		return 1;
	}

	while(shmp->strength != -2) sleep(1);
	
	printf("Calculating no. of alphanumeric and special characters...\n");
	
	for(int i=0; i<10; i++){
		if(isalnum(shmp->password[i])) (shmp->alphanum)++;
		else (shmp->special)++;
	}

	printf("no. of alphanumeric characters : %d\n", shmp->alphanum);
	printf("no. of special characters      : %d\n", shmp->special);

	shmp->strength = -1;

	if(shmdt(shmp) == -1){
		printf("Shared memory detatch failed\n");
		return 1;
	}

	return 0;
}
