/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:19 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/29 06:49:21 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_death(t_data *data)
{
	size_t	i;
	int		status;

	sem_wait(data->is_died); // now the sem is 0 again no body will enter again ;
	i = 0;
	while (i < data->num_of_philos)
	{
		kill(data->philosophers[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		waitpid(data->philosophers[i].pid, &status, 0);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->is_died);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/is_died");
	exit(0);
}