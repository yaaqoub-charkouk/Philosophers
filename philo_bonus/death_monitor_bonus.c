/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:19 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/30 16:32:24 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death(void	*parameter)
{
	t_philo *philosophers;
	int status;
	size_t	i;

	philosophers = (t_philo *)parameter;
	// printf("%zu death monitor is waiting\n", get_current_time(philosophers->data));
	// sem_wait(philosophers->data->is_died);

	i = 0;
	while (i < philosophers->data->num_of_philos)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			// printf("status  %d\n", WEXITSTATUS(status) );
			if (WEXITSTATUS(status) == 1)
			{
				i = 0;
				while (i < philosophers->data->num_of_philos)
				{
					kill(philosophers[i].pid, SIGKILL);
					// printf("%d\n", philosophers[i].pid);
					i++;
				}
				break ;
			}
			else
				i++;
		}
	}
	sem_close(philosophers->data->forks);
	sem_close(philosophers->data->print);
	sem_close(philosophers->data->is_died);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/is_died");
	// printf("before exiting");
	// exit(0);
	return (NULL);
}
