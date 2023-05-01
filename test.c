// Define a global variable to keep track of whether a philosopher has died
int philosopher_died = 0;

// Function to handle when a philosopher dies
void die(int philosopher_number, long timestamp) {
    printf("%ld %d died\n", timestamp, philosopher_number);
    philosopher_died = 1;
}

// Function to simulate the life cycle of a philosopher
void* philosopher_life(void* arg) {
    int philosopher_number = *(int*)arg;
    long last_meal_time = get_current_time(); // initialize the last meal time to the start time
    int meals_eaten = 0; // initialize the number of meals eaten to 0

    while (!philosopher_died) { // continue as long as no philosopher has died
        // thinking
        printf("%ld %d is thinking\n", get_current_time(), philosopher_number);
        usleep(TIME_TO_THINK * 1000);

        // take the left fork
        pthread_mutex_lock(&forks[philosopher_number - 1]);
        printf("%ld %d has taken fork %d\n", get_current_time(), philosopher_number, philosopher_number);
        
        // take the right fork
        pthread_mutex_lock(&forks[philosopher_number % NUM_PHILOSOPHERS]);
        printf("%ld %d has taken fork %d\n", get_current_time(), philosopher_number, philosopher_number % NUM_PHILOSOPHERS);

        // eating
        printf("%ld %d is eating\n", get_current_time(), philosopher_number);
        usleep(TIME_TO_EAT * 1000);
        meals_eaten++;
        last_meal_time = get_current_time();

        // release the forks
        pthread_mutex_unlock(&forks[philosopher_number - 1]);
        pthread_mutex_unlock(&forks[philosopher_number % NUM_PHILOSOPHERS]);

        // sleeping
        printf("%ld %d is sleeping\n", get_current_time(), philosopher_number);
        usleep(TIME_TO_SLEEP * 1000);

        // check if the philosopher has eaten enough meals
        if (NUM_MEALS > 0 && meals_eaten == NUM_MEALS) {
            break; // exit the loop if the philosopher has eaten enough meals
        }

        // check if the philosopher has taken too long to start their next meal
        if (get_current_time() - last_meal_time > TIME_TO_DIE) {
            die(philosopher_number, get_current_time()); // call the die function and exit the loop
            break;
        }
    }

    pthread_exit(NULL);
}
