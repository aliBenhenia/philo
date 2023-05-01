#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include <sys/time.h>
// typedef struct t_data
// {
//     int num_of_philo;
//     int time_eat;
//     int time_sleep;
//     int time_die;
//     int num_of_time_to_eat;
//     // pthread_mutex_t   forks;
//     t_philo *philo;
// }t_data;

typedef struct t_philo
{
    int key;
    int num_of_philo;
    int time_eat;
    int time_sleep;
    int time_die;
    int num_of_time_to_eat;
    unsigned long last_time_eat;
    int nbr_meal;
    pthread_mutex_t   fork;  // mutex variable 
    pthread_t thread;
    struct timeval tv;
    struct timeval tv2;
    struct t_philo *next;

}t_philo;