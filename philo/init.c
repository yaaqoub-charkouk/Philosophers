/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 06:52:53 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/25 08:55:44 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data_struct(t_data *data, char **av)
{
	data->zero_time = get_zero_time();
	if (data->zero_time == 0)
		return (0);
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
		return (write(2, "Error\nInvalid argument", 22), 0);
	return (1);
}

int	join_threads(t_philo *philosophers, t_data *data)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = pthread_join(data->death_monitor, NULL);
	while (i < data->num_of_philos)
	{
		if (ret)
		{
			if (ret == ESRCH)
				write(2, "Error: Thread not found or already finished.\n", 44);
			else if (ret == EINVAL)
				write(2, "Error: Invalid thread ID or already detached.\n", 47);
			else
				write(2, "Error: pthread_join failed.\n", 21);
			detach_all_threads(philosophers, data);
			clean_up(data, data->num_of_philos, 3);
			return (free(philosophers), 0);
		}
		ret = pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	clean_up(data, data->num_of_philos, 3);
	free(philosophers);
	return (1);
}

int	mutex_init(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (clean_up(data, i - 1, 0), 0);
		i++;
	}
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (clean_up(data, data->num_of_philos - 1, 1), 0);
	if (pthread_mutex_init(&data->eat_mutex, NULL))
		return (clean_up(data, data->num_of_philos - 1, 2), 0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (clean_up(data, data->num_of_philos - 1, 3), 0);
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
	if (!mutex_init(data))
		return (0);
	if (pthread_create(&philosophers[i].thread, NULL,
			routine, &philosophers[i]))
	{
		write (2, "Error\n faild to create thread .", 32);
		clean_up(data, data->num_of_philos, 3);
		return (0);
	}
	return (1);
}

int	init_philo_struct(t_philo *philosophers, t_data *data)
{
	size_t	i;

	i = 0;
	data->forks = NULL;
	data->forks = malloc(data->num_of_philos * sizeof(t_mutex));
	if (!data->forks)
	{
		clean_up(data, 0, 0);
		return (free(philosophers), 0);
	}
	while (i < data->num_of_philos)
	{
		if (!init_philo_helper(philosophers, data, i))
			return (free(philosophers), 0);
		i++;
	}
	if (pthread_create(&data->death_monitor, NULL,
			death_monitoring, philosophers))
		return (free(philosophers), clean_up(data, data->num_of_philos, 3), 0);
	if (!join_threads(philosophers, data))
		return (0);
	return (1);
}
