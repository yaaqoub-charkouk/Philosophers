#include "../philo.h"

void	ft_free(t_data *data, t_philo **philo, int i)
{
	if (*philo)
	{
		free(*philo);
		*philo = NULL;
	}
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
	int i;


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
