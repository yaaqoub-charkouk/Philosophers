/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:38:00 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/27 07:59:25 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return (1);
		if (!init_philo_struct(philosophers, &data))
			return (1);
	}
	else
		printf("Error\nInvalid arguments ");
	return (0);
}
