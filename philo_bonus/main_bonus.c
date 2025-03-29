/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:12 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/29 12:35:53 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_until_finished(t_data *data)
{
	sem_wait(data->is_finished);
	sem_wait(data->is_finished);
	sem_wait(data->is_finished);
	sem_wait(data->is_finished);
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers;

	if (ac == 5 || ac == 6)
	{
		init_data_struct(&data, av);
		philosophers = malloc(data.num_of_philos * sizeof(t_philo));
		if (!philosophers)
			return (write (2, "allocation failure .\n", 23), 1);
		create_philo_process(&data, philosophers);
		monitor_death(&data, philosophers);
		wait_until_finished(&data);
	}
	else
		write(2, "Error\n Invalid args", 21);
	return (0);
}
