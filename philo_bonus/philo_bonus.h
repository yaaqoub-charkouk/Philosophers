/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:36:24 by ycharkou          #+#    #+#             */
/*   Updated: 2025/03/29 12:13:33 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	size_t		num_of_philos;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			max_eating_count_p;
	time_t		zero_time;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*is_died;
}	t_data;

typedef struct s_philo
{
	size_t	id;
	pid_t	pid;
	t_data	*data;
	int		num_eaten;
}	t_philo;

//routine
void	routine(t_data *data, t_philo *philo);

int		init_data_struct(t_data *data, char **av);
int		create_philo_process(t_data *data, t_philo *philos);
int		ft_atoi(const char *str);

//time
time_t	get_current_time(t_data	*data);
time_t	get_zero_time(void);

// death
void	monitor_death(t_data *data, t_philo	*philosophers);

#endif