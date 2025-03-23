#include "philo.h"

int	init_data_struct(t_data *data, char **av)
{
	 //mutex init for death monitothread
	data->is_died = 0;
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->zero_time = get_zero_time(); // to get the initial time;
	if (data->zero_time == 0)
		return (0);// failed to get time !!!!!!!!!!!! get time of the day
	if (av[5] != NULL)
		data->max_eating_count_p = ft_atoi(av[5]);
	else
		data->max_eating_count_p = -1;
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
			ft_free(data, &philosophers, i); // should i destroy mutex ??
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
	pthread_mutex_init(&data->eat, NULL); // just for testing the function of last eat , trying to avoid data race 
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL)) // JUST TO AVOID DATA RACE
			return (ft_free(data, &philosophers, i - 1), 0); // so that the current was not initialized ;
		i++;
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
		philosophers[i].id = i + 1;
		philosophers[i].last_time_eats = 0;
		philosophers[i].num_times_eats = 0;
		philosophers[i].left_fork = &data->forks[i];
		philosophers[i].right_fork = &data->forks[(i + 1) % data->num_of_philos];  
		philosophers[i].data = data;
		if (mutex_init(philosophers, data) == 0)
			return (0); // initialize mutex; freed befor return , in function
		if (pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]))
		{
			write (2, "Error\n faild to create thread .", 32);
			free_and_destroy(data, &philosophers);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) || pthread_mutex_init(&data->print_mutex, NULL))
		return (free_and_destroy(data, &philosophers), 0);
	pthread_create(&data->death_monitor, NULL, death_monitoring, philosophers);
	pthread_join(data->death_monitor, NULL);
	join_threads(philosophers, data); // until now everything was good ,no problem occurs
	return (1);
}
