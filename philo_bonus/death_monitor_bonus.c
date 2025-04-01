/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:19 by ycharkou          #+#    #+#             */
/*   Updated: 2025/04/01 19:58:26 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_log(t_data *data, size_t id, char *log)
{
	sem_wait(data->print);
	printf("%zu %zu %s\n", get_current_time(data), id, log);
	sem_post(data->print);
}

void	close_sem(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->death_sem);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death_sem");
}

void	monitor_death(t_philo	*philosophers)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < philosophers->data->num_of_philos)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			if (WEXITSTATUS(status) == 1)
			{
				i = 0;
				while (i < philosophers->data->num_of_philos)
				{
					kill(philosophers[i].pid, SIGKILL);
					i++;
				}
				break ;
			}
			else
				i++;
		}
	}
	close_sem(philosophers->data);
}
