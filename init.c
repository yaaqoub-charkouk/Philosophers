#include "philo.h"
#include <limits.h>

int	init_data_struct(t_data *data, char **av)
{
	data->zero_time = get_zero_time();
	if (data->zero_time == 0)
		return (0);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->is_died = 0;
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		data->max_eating_count_p = ft_atoi(av[5]);
	else
		data->max_eating_count_p = -2;
	if (data->num_of_philos == SIZE_T_MAX || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1
		|| data->max_eating_count_p == -1)
		return (printf("Error\nInvalid argument"), 0);
	return (1);
}

int	join_threads(t_philo *philosophers, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(philosophers[i].thread, NULL))
		{
			write(2, "pthread_join failed .\n", 21);
			ft_free(data, &philosophers, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	mutex_init(t_philo *philosophers, t_data *data)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&data->eat, NULL);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_free(data, &philosophers, i - 1), 0);
		i++;
	}
	return (1);
}

int	init_philo_helper(t_philo *philosophers, t_data *data, int i)
{
	philosophers[i].id = i + 1;
	philosophers[i].last_time_eats = 0;
	philosophers[i].num_times_eats = 0;
	philosophers[i].left_fork = &data->forks[i];
	philosophers[i].right_fork = &data->forks[(i + 1) % data->num_of_philos];  
	philosophers[i].data = data;
	if (mutex_init(philosophers, data) == 0)
		return (0);
	if (pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]))
	{
		write (2, "Error\n faild to create thread .", 32);
		free_and_destroy(data, &philosophers);
		return (0);
	}
	return (1);
}

int	init_philo_struct(t_philo *philosophers, t_data *data)
{
	size_t i;

	i = 0;
	data->forks = malloc(data->num_of_philos * sizeof(mutex_t));
	if (!data->forks)
	{
		ft_free(data, &philosophers, 0);
		return (0);
	}

	while (i < data->num_of_philos)
	{
		if (!init_philo_helper(philosophers, data, i))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (free_and_destroy(data, &philosophers), 0);
	pthread_create(&data->death_monitor, NULL, death_monitoring, philosophers);
	pthread_join(data->death_monitor, NULL);
	join_threads(philosophers, data);
	return (1);
}
