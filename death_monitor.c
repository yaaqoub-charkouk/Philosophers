#include "philo.h"

int	get_flag_value(int died, t_data *data)
{
	int	rs;

	rs = 0;
	pthread_mutex_lock(&data->death_mutex);
	if (died)
	{
		data->is_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (0);
	}
	else
		rs = data->is_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (rs);
}

int is_died(t_philo *philo)
{
	size_t	i;
	time_t	last_time_eats;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		// last_time_eats = get_last_time_eats(philo[i]);
		last_eat(philo, 0, &last_time_eats);

		if ((get_current_time(philo->data) - last_time_eats) > philo[i].data->time_to_die)
		{
			// pthread_mutex_lock(&philo->data->death_mutex);
			// philo->data->is_died = 1;
			// pthread_mutex_unlock(&philo->data->death_mutex);
			get_flag_value(1, philo->data);
			// to write in died , with flag == 1;
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("%zu %zu died\n", get_current_time(philo->data), philo[i].id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (1);
		}
		i++;
		// usleep(500);
	}
	return (0);
}

void	*death_monitoring(void *philos)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)philos;
	while (1)
	{
		if (is_died(philos))
			break ;
		usleep(1000);
	}
	return (NULL);
}