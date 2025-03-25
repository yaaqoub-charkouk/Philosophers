/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:18:49 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/25 12:15:32 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_up(t_data *data, size_t	i, int flag)
{
	size_t	j;

	if (flag == 3)
	{
		j = 0;
		while (j < data->num_of_philos)
			pthread_mutex_destroy(&data->forks[j++]);
		free(data->forks);
		data->forks = NULL;
	}
	if (data->forks && i < data->num_of_philos && i != 0)
	{
		while (i >= 0)
			pthread_mutex_destroy(&data->forks[i--]);
		free(data->forks);
		data->forks = NULL;
		write(2, "Error\nFailed to init mutex. ", 28);
	}
	if (flag >= 1)
		pthread_mutex_destroy(&data->death_mutex);
	if (flag >= 2)
		pthread_mutex_destroy(&data->eat_mutex);
	if (flag >= 3)
		pthread_mutex_destroy(&data->print_mutex);
}

int	detach_all_threads(t_philo *philosophers, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_detach(philosophers[i].thread))
		{
			write(2, "Error: Failed to detach thread\n", 31);
		}
		i++;
	}
	return (1);
}
