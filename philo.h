/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:44:18 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/18 12:42:12 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "utils/utils.h"

#define THINKING 0
#define EATING 1
#define SLEEPING 2 

typedef pthread_mutex_t mutex_t;
typedef struct s_data t_data;

typedef struct s_philo
{
	int			id;
	size_t		last_time_eats;
	int 		num_times_eats;	
	mutex_t		*left_fork;
	mutex_t		*right_fork;
	pthread_t	thread;
	t_data		*data; // each philo should have access to global data
}	t_philo;

typedef struct s_data
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_eating_count_p; // optional 
	mutex_t	*forks;
	size_t	zero_time;
	int		is_died;
}	t_data;

int		init_data_struct(t_data *data, char **av);
int		init_philo_struct(t_philo *philosophers, t_data *data);
void	ft_free(t_data *data, t_philo **philo, int i);
void	*routine(void *param);
void	free_and_destroy(t_data *data, t_philo **philo);

size_t	get_current_time(t_data *data);
size_t	get_zero_time(void);

// actions
void	eat(t_philo *philo);
void	sleep(t_philo *philo);
void	think(t_philo *philo);

#endif