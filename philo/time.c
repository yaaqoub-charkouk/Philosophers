/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:46:41 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/25 08:47:04 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_current_time(t_data	*data)
{
	struct timeval	time;
	size_t			current_time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write (1, "get_time_of_day() error\n", 24);
		return (0);
	}
	current_time = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->zero_time;
	return (current_time);
}

time_t	get_zero_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write (1, "get_time_of_day() error\n", 24);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(time_t time, t_data *data)
{
	time_t	start;

	start = get_zero_time();
	while (get_zero_time() - start < time)
	{
		if (get_death(data))
			break ;
		usleep(100);
	}
}
