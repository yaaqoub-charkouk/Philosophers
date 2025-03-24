/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:46:12 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/24 12:47:41 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_philo *philo, int *is_finished)
{
	size_t	i;
	int		num_eat;
	time_t	last_time_eats;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		last_eat(philo, 0, &last_time_eats, &num_eat);
		if ((get_current_time(philo->data) - last_time_eats) 
			> philo[i].data->time_to_die)
		{
			set_death(philo->data);
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("\033[1;31m%zu %zu died\033[0m\n",
				get_current_time(philo->data), philo[i].id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (1);
		}
		if (philo->data->max_eating_count_p != -2 
			&& num_eat == philo->data->max_eating_count_p)
			*is_finished = 1;
		i++;
		usleep(500);
	}
	return (0);
}

void	*death_monitoring(void *philos)
{
	t_philo	*philosophers;
	int		is_finished;

	philosophers = (t_philo *)philos;
	while (1)
	{
		if (is_died(philos, &is_finished))
			break ;
		if (is_finished)
		{
			set_death(philosophers->data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
