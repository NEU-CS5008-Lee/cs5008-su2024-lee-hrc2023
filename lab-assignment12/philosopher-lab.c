// Haoyang Chen
// chen.haoyang4@northeastern.edu
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t chopstick[5];//lock variable
int finished[5] = {0}; // Track if philosophers are finished eating

// Thread to be executed
void *philosopher(void *x)
{
    // Treat variable x as a pointer to an int and then extract the value into n
    int *a = (int *)x;
    int n = *a;

    // Philosopher is thinking
    printf("Philosopher %d is thinking\n", n);
    sleep(1);

    // Philosopher is hungry and tries to pick up the chopsticks
    printf("Philosopher %d is hungry\n", n);

    // Use mutex locks to pick up chopsticks
    if (n % 2 == 0)
    {
        pthread_mutex_lock(&chopstick[n]); // Pick up left chopstick
        pthread_mutex_lock(&chopstick[(n + 1) % 5]); // Pick up right chopstick
    }
    else
    {
        pthread_mutex_lock(&chopstick[(n + 1) % 5]); // Pick up right chopstick
        pthread_mutex_lock(&chopstick[n]); // Pick up left chopstick
    }

    // Philosopher is eating
    printf("Philosopher %d is eating\n", n);
    sleep(1);

    // Put down chopsticks
    pthread_mutex_unlock(&chopstick[n]);
    pthread_mutex_unlock(&chopstick[(n + 1) % 5]);

    printf("Philosopher %d finished eating and put down chopsticks\n", n);

    // Mark philosopher as finished
    finished[n] = 1;

    return NULL;
}

/*------------ Main Program---------*/
int main()
{
    int i,val[5];
    pthread_t threads[5];
    //initializing the mutex (for chopsticks)
    for(i=0;i<5;i++){
        pthread_mutex_init(&chopstick[i],NULL);
    }   

    //create and run the thread
    for(i=0;i<5;i++){
        val[i]=i;
        pthread_create(&threads[i],NULL,(void *)philosopher,&val[i]);
    }
    
    //wait until all the threads are done
    for(i=0;i<5;i++){
        pthread_join(threads[i],NULL);
    }
    
    // Destroying the mutex
    for(i=0;i<5;i++){
        pthread_mutex_destroy(&chopstick[i]);
    }
    
    return 0;
}