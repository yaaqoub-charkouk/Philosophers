/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:12 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/30 15:56:28 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_until_finish(void	*parameter)
{
	size_t i;
	t_philo	*philo;
	
	philo = (t_philo *)parameter;
	i = 0;
	while (i < philo->data->num_of_philos)
	{
		printf("yaaqoub\n");
		sem_wait(philo->data->is_finished);
		i++;
	}
	sem_post(philo->data->is_died);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers;
	// int		status;
	// size_t	i;
	// pthread_t	death_monitor;
	// pthread_t	finish_monitor;

	if (ac == 5 || ac == 6)
	{
		if (!init_data_struct(&data, av))
			return (1);
		philosophers = malloc(data.num_of_philos * sizeof(t_philo));
		if (!philosophers)
			return (write(2, "Allocation failure\n", 18), 1);
		if (!create_philo_process(&data, philosophers))
			return (free(philosophers), 1);
		// wait_until_finish(philosophers);
		monitor_death(philosophers);
		// pthread_join(finish_monitor, NULL);
		// pthread_join(death_monitor, NULL);


		// pthread_detach(death_monitor);
		// pthread_detach(finish_monitor);
		
		free(philosophers);
		sem_close(data.forks);
		sem_close(data.print);
		sem_close(data.is_died);
		sem_close(data.is_finished);
		sem_unlink("/forks");
		sem_unlink("/print");
		sem_unlink("/is_died");
		sem_unlink("/is_finished");
	}
	else
	{
		write(2, "Error: Invalid arguments\n", 24);
		return (1);
	}
	return (0);
}
