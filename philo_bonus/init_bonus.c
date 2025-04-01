/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:16 by ycharkou          #+#    #+#             */
/*   Updated: 2025/04/01 19:44:27 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/is_died");
	sem_unlink("/death_sem");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL,
			0644, data->num_of_philos);
	data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	data->death_sem = sem_open("/death_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->death_sem == SEM_FAILED)
		return (write(2, "Error sem open failed", 23), 0);
	return (1);
}

int	init_data_struct(t_data *data, char **av)
{
	data->zero_time = get_zero_time();
	if (data->zero_time == 0)
		return (0);
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
	if (!init_semaphores(data))
		return (0);
	return (1);
}

int	create_philo_process(t_data *data, t_philo *philosophers)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		philosophers[i].num_eaten = 0;
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		philosophers[i].last_meal = get_current_time(data);
		philosophers[i].pid = fork(); 
		if (philosophers[i].pid < 0)
			return (write(2, "fork() Failed.", 16), 0);
		else if (philosophers[i].pid == 0)
		{
			routine(data, &philosophers[i]);
			exit(0);
		}
		i++;
	}
	return (1);
}
