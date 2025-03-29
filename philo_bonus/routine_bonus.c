#include "philo_bonus.h"

void    write_log(t_data *data, size_t id, char *log)
{
	sem_wait(data->print);
	printf("%zu %zu %s\n", get_current_time(data), id, log);
	sem_post(data->print);
}

void    ft_usleep(time_t time, t_data *data, t_philo *philo,time_t last_meal)
{
        time_t  start;

        start = get_zero_time();
        while (get_zero_time() - start < time)
        {
			if (get_current_time(data) - last_meal >= data->time_to_die)
			{
				// write_log(data, philo->id, "died");
				sem_wait(data->print);
				printf("\033[1;31m%zu %zu died\033[0m\n",get_current_time(data), philo->id);
				sem_post(data->is_died);
				exit(0);
			}
			usleep(100);
        }
}

void    routine(t_data *data, t_philo *philo)
{
	time_t  last_meal;

	last_meal = get_current_time(data);
	if (data->num_of_philos == 1)
	{
		usleep(data->time_to_eat * 1000);
		write_log(data, philo->id, "died");
		sem_post(data->is_died);
		exit(0);
	}
	while (1)
	{
		// Check for starvation before attempting to take forks
		// Take forks
		sem_wait(data->forks);
		write_log(data, philo->id, "has taken a fork");
		sem_wait(data->forks);
		write_log(data, philo->id, "has taken a fork");
		// Update last_meal immediately after getting forks
		last_meal = get_current_time(data);
		write_log(data, philo->id, "is eating");
		ft_usleep(data->time_to_eat, data, philo, last_meal);
		// Release forks
		sem_post(data->forks);
		sem_post(data->forks);
		// Sleep and think
		write_log(data, philo->id, "is sleeping");
		ft_usleep(data->time_to_eat, data, philo, last_meal);
		// usleep(data->time_to_sleep * 1000);
		write_log(data, philo->id, "is thinking");
		if (get_current_time(data) - last_meal >= data->time_to_die)
		{
			// write_log(data, philo->id, "died");
			sem_wait(data->print);
			printf("\033[1;31m%zu %zu died\033[0m\n",get_current_time(data), philo->id);
			sem_post(data->is_died);
			exit(0);
		}
	}
}