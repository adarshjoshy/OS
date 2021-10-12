#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
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
	
	printf("Enter password: ");
	scanf("%s", shmp->password);
	if(strlen(shmp->password) != 10){
		printf("Entered password is not of length 10\n");
		return 1;
	}

	shmp->strength = -2;

	while(shmp->strength < 0) sleep(1);

	if(shmp->strength == 1){
		printf("The password is strong\n");
	}
	else if(shmp->strength == 0){
		printf("The password is weak\n");
	}

	if(shmdt(shmp) == -1){
		printf("Shared memory detatch failed\n");
		return 1;
	}

	if(shmctl(shmid, IPC_RMID, NULL) == -1){
		printf("Shared memory control failed\n");
		return 1;
	}

	return 0;
}
