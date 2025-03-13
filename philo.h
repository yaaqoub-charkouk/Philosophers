/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:44:18 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/13 11:48:15 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef pthread_mutex_t mutex_t;

typedef struct s_philo
{
	int			id;
	int			last_time_eats;
	int 		num_times_eats;	
	mutex_t		*left_fork;
	mutex_t		*right_fork;
	pthread_t	thread;
}	t_philo;

typedef struct s_data
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_eating_count_p;
}	t_data;

#endif