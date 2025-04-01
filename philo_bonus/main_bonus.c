/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:13:12 by ycharkou          #+#    #+#             */
/*   Updated: 2025/04/01 19:04:08 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers;

	if (ac == 5 || ac == 6)
	{
		if (!init_data_struct(&data, av))
			return (1);
		philosophers = malloc(data.num_of_philos * sizeof(t_philo));
		if (!philosophers)
			return (write(2, "Allocation failure\n", 18), 1);
		if (!create_philo_process(&data, philosophers))
			return (free(philosophers), 1);
		monitor_death(philosophers);
		free(philosophers);
	}
	else
	{
		write(2, "Error: Invalid arguments\n", 24);
		return (1);
	}
	return (0);
}
