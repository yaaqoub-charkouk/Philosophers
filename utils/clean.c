#include "../philo.h"

void	ft_free(t_data *data, t_philo **philo, size_t i)
{
	if (*philo)
	{
		free(*philo);
		*philo = NULL;
	}
	if (i == 0)
		pthread_mutex_destroy(&data->death_mutex); // the function will be called with 0 if the first mutex was not successfully initialized;
	if (data->forks)
	{
		while (i >= 0 && i < data->num_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i--]);
		}
		free(data->forks);
		data->forks = NULL;
	}
}

void	free_and_destroy(t_data *data, t_philo **philo)
{
	size_t i;


	if (*philo)
	{
		free(*philo);
		*philo = NULL;
	}
	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
}
