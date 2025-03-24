/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:47:47 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/24 12:47:48 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->is_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

int	get_death(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->death_mutex);
	flag = data->is_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (flag);
}