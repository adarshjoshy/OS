#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <unistd.h>

#define N 5
#define TRUE 1
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

sem_t mutex; 
sem_t s[N];

void test(int i){
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
        state[i] = EATING;
        sleep(2);
        printf("P%d picks fork %d and %d up\n", i+1, LEFT+1, i+1);
        printf("P%d: EATING\n", i+1);
        sem_post(&s[i]);                            //up(s[i])
    }
}

void pick_forks(int i){
    sem_wait(&mutex);                               //lock(mutex)
    state[i] = HUNGRY;
    printf("P%d: HUNGRY\n", i+1);
    test(i);
    sem_post(&mutex);                                //unlock(mutex)
    sem_wait(&s[i]);                                 //down(s[i])
    sleep(1);
}

void put_forks(int i){
    sem_wait(&mutex);                               //lock(mutex)
    state[i] = THINKING;
    printf("P%d puts fork %d and %d down\n", i+1, LEFT+1, i+1); 
    printf("P%d: THINKING\n", i+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);                               //unlock(mutex)
}

void* philosopher(void* phil){
    while(TRUE){
        int* i = phil;
        sleep(1);
        pick_forks(*i);
        sleep(0);
        put_forks(*i);
    }
}

int main(){
    
    //initialize semaphores
    sem_init(&mutex, 0, 1);
    for(int i=0; i<N; i++) sem_init(&s[i], 0, 0);

    pthread_t t[N];
    for(int i=0; i<N; i++){
        pthread_create(&t[i], NULL, philosopher, &phil[i]);
    }
    for(int i=0; i<N; i++){
        pthread_join(t[i], NULL);
        printf("P%d: THINKING\n", i+1);
    }

    return 0;
}
