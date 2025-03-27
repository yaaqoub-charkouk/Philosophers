/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:42:02 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/27 08:42:43 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_set_last_eat(t_philo *philo, int flag, time_t *time, int *num_eat)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	if (flag == 1)
	{
		philo->last_time_eats = get_current_time(philo->data);
		philo->num_times_eats++;
	}
	else
	{
		if (time)
			*time = philo->last_time_eats;
		*num_eat = philo->num_times_eats;
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		write_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		write_log(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		write_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		write_log(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	int		current_eats;

	get_set_last_eat(philo, 0, NULL, &current_eats);
	if (current_eats == philo->data->max_eating_count_p)
		return ;
	take_fork(philo);
	write_log(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	get_set_last_eat(philo, 1, 0, 0);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	write_log(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	write_log(philo, "is thinking");
}
