#include "philo_bonus.h"

void    write_log(t_data *data, size_t id, char *log)
{
    sem_wait(data->print);
    printf("%zu %zu %s\n", get_current_time(data), id, log);
    sem_post(data->print);
}

void    routine(t_data *data, t_philo *philo)
{
    time_t  last_meal;

    last_meal = get_current_time(data);
    while (1)
    {
        // Check for starvation before attempting to take forks
        if (get_current_time(data) - last_meal >= data->time_to_die)
        {
            write_log(data, philo->id, "died");
            sem_post(data->is_died);
            exit(0);
        }
        // Take forks
        sem_wait(data->forks);
        write_log(data, philo->id, "has taken a fork");
        sem_wait(data->forks);
        write_log(data, philo->id, "has taken a fork");
        // Update last_meal immediately after getting forks
        last_meal = get_current_time(data);
        write_log(data, philo->id, "is eating");
        usleep(data->time_to_eat * 1000);
        // Release forks
        sem_post(data->forks);
        sem_post(data->forks);
        // Sleep and think
        write_log(data, philo->id, "is sleeping");
        usleep(data->time_to_sleep * 1000);
        write_log(data, philo->id, "is thinking");
    }
}