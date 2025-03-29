/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:16 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/29 06:50:59 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_of_philos);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->is_died = sem_open("/is_died", O_CREAT, 0644, 0);
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
	init_semaphores(data); // to initialize semaphores,
	return (1);
}

int	create_philo_process(t_data *data, t_philo *philosophers) // from here process start execution
{
	int	i;

	data->philosophers = philosophers; // so that the data have reference to philo struct , and it will be able to kill all process 
	i = 0;
	while (i < data->num_of_philos)
	{
		philosophers[i].id = i + 1; // here we give the philo an id
		philosophers[i].pid = fork(); 
		if (philosophers[i].pid < 0)
			return (write(2, "fork() Failed.", 16), 0);
		else if (philosophers[i].pid == 0)
		{
			routine(data, &philosophers[i]);
			exit(0); // just to make sure , each child process must exit and the child will execute just until this step
		}
		i++;
	}
	return (1);
}