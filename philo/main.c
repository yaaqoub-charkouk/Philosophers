/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:38:00 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/25 11:13:36 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	leaks_test()
{
	system("leaks philo");
}
int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers;

	atexit(leaks_test);
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
		printf("Error\n");
	return (0);
}
