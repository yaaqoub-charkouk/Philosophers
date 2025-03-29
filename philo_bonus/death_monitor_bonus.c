/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:19 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/29 12:05:36 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_death(t_data *data, t_philo *philosophers)
{
	size_t	i;

	sem_wait(data->is_died);
	i = 0;
	while (i < data->num_of_philos)
	{
		kill(philosophers[i].pid, SIGKILL);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->is_died);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/is_died");
	exit(0);
}
