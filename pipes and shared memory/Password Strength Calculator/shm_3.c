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

	while(shmp->strength != -1) sleep(1);
	
	printf("Deciding strength of password...\n");
	
	if(shmp->alphanum >= shmp->special) shmp->strength = 0;
	else shmp->strength = 1;

	printf("Strength: %d\n", shmp->strength);

	if(shmdt(shmp) == -1){
		printf("Shared memory detatch failed\n");
		return 1;
	}

	return 0;
}
