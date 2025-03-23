/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:44:18 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/23 09:49:49 by ycharkou         ###   ########.fr       */
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
	size_t		id;
	time_t		last_time_eats;
	size_t 		num_times_eats;	
	mutex_t		*left_fork;
	mutex_t		*right_fork;
	pthread_t	thread;
	t_data		*data; // each philo should have access to global data
	// mutex_t		philo_mutex;
}	t_philo;

typedef struct s_data
{
	size_t		num_of_philos;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			max_eating_count_p; // optional 
	time_t		zero_time;
	mutex_t		*forks;
	mutex_t		death_mutex;
	mutex_t		print_mutex;
	
	pthread_t	death_monitor; // create it at init
	int			is_died;

	mutex_t		eat;
}	t_data;

int		init_data_struct(t_data *data, char **av);
int		init_philo_struct(t_philo *philosophers, t_data *data);
void	ft_free(t_data *data, t_philo **philo, size_t i);
void	*routine(void *param);
void	free_and_destroy(t_data *data, t_philo **philo);

time_t	get_current_time(t_data *data);
time_t	get_zero_time(void);

// actions
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);

void	ft_usleep(time_t time, t_data *data);

void	ft_printf(t_philo *philo, char *message);

//death monitoring
void	*death_monitoring(void *philos);
// int		is_still_alive(t_data	*data);

// just for testing
int	get_flag_value(int died, t_data *data);
void    last_eat(t_philo *philo, int flag, time_t *time);
#endif