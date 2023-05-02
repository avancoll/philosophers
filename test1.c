#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

// Define a struct to represent a philosopher
typedef struct {
    int id;
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    struct timeval last_meal;
} philosopher_t;

// Function to pick up a fork
void pick_up_fork(pthread_mutex_t* fork) {
    pthread_mutex_lock(fork);
}

// Function to put down a fork
void put_down_fork(pthread_mutex_t* fork) {
    pthread_mutex_unlock(fork);
}

// Function to simulate a philosopher thinking
void think(int id) {
    printf("Philosopher %d is thinking.\n", id);
}

// Function to simulate a philosopher eating
void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
}

// Function to get the current time in microseconds
long get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

// Function to simulate a philosopher's behavior
void* philosopher(void* arg) {
    philosopher_t* phil = (philosopher_t*) arg;

    while (1) {
        think(phil->id);

        pick_up_fork(phil->left_fork);
        pick_up_fork(phil->right_fork);

        eat(phil->id);
        usleep(phil->time_to_eat);

        put_down_fork(phil->left_fork);
        put_down_fork(phil->right_fork);

        gettimeofday(&(phil->last_meal), NULL);
        usleep(phil->time_to_sleep);

        // Check if the philosopher has exceeded the time to die constraint
        long current_time = get_current_time();
        long time_since_last_meal = current_time - (phil->last_meal.tv_sec * 1000000 + phil->last_meal.tv_usec);
        if (time_since_last_meal > phil->time_to_die) {
            printf("Philosopher %d has died.\n", phil->id);
            break;
        }
    }

    pthread_exit(NULL);
}

// Function to initialize a philosopher
void initialize_philosopher(philosopher_t* phil, int id, pthread_mutex_t* left_fork, pthread_mutex_t* right_fork, int time_to_die, int time_to_eat, int time_to_sleep) {
    phil->id = id;
    phil->left_fork = left_fork;
    phil->right_fork = right_fork;
    phil->time_to_die = time_to_die;
    phil->time_to_eat = time_to_eat;
    phil->time_to_sleep = time_to_sleep;
    gettimeofday(&(phil->last_meal), NULL);
}

int main(int argc, char** argv) {
    if (argc != 5) {
        printf("Usage: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep\n");
        return 1;
    }

    // Parse arguments
    int num_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);
// Initialize forks
pthread_mutex_t forks[num_philosophers];
for (int i = 0; i < num_philosophers; i++) {
    pthread_mutex_init(&forks[i], NULL);
}

// Initialize philosophers
philosopher_t philosophers[num_philosophers];
for (int i = 0; i < num_philosophers; i++) {
    initialize_philosopher(&philosophers[i], i, &forks[i], &forks[(i+1) % num_philosophers], time_to_die, time_to_eat, time_to_sleep);
}

// Create threads for each philosopher
pthread_t threads[num_philosophers];
for (int i = 0; i < num_philosophers; i++) {
    pthread_create(&threads[i], NULL, philosopher, &philosophers[i]);
}

// Wait for threads to finish
for (int i = 0; i < num_philosophers; i++) {
    pthread_join(threads[i], NULL);
}

// Destroy forks
for (int i = 0; i < num_philosophers; i++) {
    pthread_mutex_destroy(&forks[i]);
}

return 0;

}
