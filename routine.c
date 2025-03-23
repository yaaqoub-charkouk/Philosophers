#include "philo.h"

int	is_still_alive(t_data	*data)
{
	int	flag;

	flag = 1;
	pthread_mutex_lock(&data->death_mutex);
	flag = data->is_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (!flag);
}

void	ft_printf(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (is_still_alive(philo->data)) // lock mutex
		printf("%zu %zu %s\n", get_current_time(philo->data), philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*routine(void *param)
{
	t_philo *philosopher;

	philosopher = (t_philo *)param;
	if (philosopher->data->num_of_philos == 1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		ft_printf(philosopher, "has taken a fork");
		ft_usleep(philosopher->data->time_to_die, philosopher->data);
		pthread_mutex_unlock(philosopher->left_fork);
		return (NULL);
	}
	if (philosopher->id % 2 == 0)
		usleep(10);
	while (is_still_alive(philosopher->data)) // lock the mutex before reading is died , after writing it in death monitoring thread
	{
		eat(philosopher);
		ft_sleep(philosopher);
		think(philosopher);
	}
	return (NULL);
}
