/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:00:37 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/29 12:22:53 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_log(t_data *data, size_t id, char *log)
{
	sem_wait(data->print);
	printf("%zu %zu %s\n", get_current_time(data), id, log);
	sem_post(data->print);
}

void	ft_usleep(time_t time, t_data *data, t_philo *philo, time_t last_meal)
{
	time_t	start;

	start = get_zero_time();
	while (get_zero_time() - start < time)
	{
		if (get_current_time(data) - last_meal >= data->time_to_die)
		{
			sem_wait(data->print);
			printf("\033[1;31m%zu %zu died\033[0m\n",
				get_current_time(data), philo->id);
			sem_post(data->is_died);
			exit(0);
		}
		if (data->max_eating_count_p != -2 && philo->num_eaten == data->max_eating_count_p)
			exit(0);
		usleep(100);
	}
}

void	take_forks(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	write_log(data, philo->id, "has taken a fork");
	sem_wait(data->forks);
	write_log(data, philo->id, "has taken a fork");
}

void	routine(t_data *data, t_philo *philo)
{
	time_t	last_meal;

	last_meal = get_current_time(data);
	if (data->num_of_philos == 1)
	{
		usleep(data->time_to_eat * 1000);
		write_log(data, philo->id, "died");
		sem_post(data->is_died);
		exit(0);
	}
	while (1)
	{
		take_forks(data, philo);
		last_meal = get_current_time(data);
		philo->num_eaten++;
		write_log(data, philo->id, "is eating");
		ft_usleep(data->time_to_eat, data, philo, last_meal);
		sem_post(data->forks);
		sem_post(data->forks);
		write_log(data, philo->id, "is sleeping");
		ft_usleep(data->time_to_eat, data, philo, last_meal);
		write_log(data, philo->id, "is thinking");
	}
}
