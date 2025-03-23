#include "philo.h"

// time_t	get_last_time_eats(t_philo *philo)
// {

// }

int is_died(t_philo *philo)
{
	size_t	i;
	time_t	last_time_eats;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		pthread_mutex_lock(&philo[i].philo_mutex);
		last_time_eats = philo[i].last_time_eats;
		pthread_mutex_unlock(&philo[i].philo_mutex);
		if ((get_current_time(philo->data) - last_time_eats) > philo[i].data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->is_died = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
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
	while (is_still_alive(philosophers->data))
	{
		if (is_died(philos))
			break ;
		usleep(1000);
	}
	return (NULL);
}