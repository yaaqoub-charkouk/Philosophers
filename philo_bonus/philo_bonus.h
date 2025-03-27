/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:36:24 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/27 13:53:14 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_data
{
	size_t		num_of_philos;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			max_eating_count_p;
	time_t		zero_time;
	int			is_died;
} t_data;

int     init_data_struct(t_data *data, char **av);


#endif