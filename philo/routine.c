/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:46:00 by ycharkou          #+#    #+#             */
/*   Updated: 2025/04/06 13:37:51 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!get_death(philo->data))
		printf("%zu %zu %s\n",
			get_current_time(philo->data), philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*routine(void *param)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)param;
	if (philosopher->data->num_of_philos == 1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		write_log(philosopher, "has taken a fork");
		ft_usleep(philosopher->data->time_to_die, philosopher->data);
		pthread_mutex_unlock(philosopher->left_fork);
		return (NULL);
	}
	if (philosopher->id % 2 == 0)
		ft_usleep(philosopher->data->time_to_eat, philosopher->data);
	while (!get_death(philosopher->data))
	{
		if (!eat(philosopher))
			return (NULL);
		ft_sleep(philosopher);
		think(philosopher);
	}
	return (NULL);
}
