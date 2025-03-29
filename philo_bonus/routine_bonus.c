/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:09 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/29 07:08:55 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_log(t_data *data, size_t id, char *log)
{
	sem_wait(data->print);
	printf("%zu %zu %s\n", get_current_time(data), id, log);
	sem_post(data->print);
}

void	routine(t_data *data, t_philo *philo)
{
	time_t	last_time_eat;

	last_time_eat = get_current_time(data);
	while (1)
	{
		printf("in routine");
		if (philo->id % 2 == 0)
			usleep(data->time_to_sleep * 1000);
		if (get_current_time(data) - last_time_eat >= data->time_to_die) // we have to check this inside usleep
		{
			write_log(data, philo->id, "died");
			sem_post(data->is_died); // another solution
			break ;
		}
		sem_wait(data->forks);
		write_log(data, philo->id, "has taken a fork");
		sem_wait(data->forks);
		write_log(data, philo->id, "has taken a fork");
		write_log(data, philo->id, "is eating");
		// philo is eating ...
		usleep(data->time_to_eat * 1000);
		// philo has eated .
		last_time_eat = get_current_time(data);
		sem_post(data->forks);
		sem_post(data->forks);
		//philo is sleeping ...
		write_log(data, philo->id, "is sleeping");
		usleep(data->time_to_sleep * 1000);
		// philo has sleeped .
		write_log(data, philo->id, "is thinking");
	}
}
