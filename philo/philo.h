/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:44:18 by ycharkou          #+#    #+#             */
/*   Updated: 2025/04/01 20:22:07 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

# define THINKING 0
# define EATING 1
# define SLEEPING 2 

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	size_t		num_of_philos;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	int			max_eating_count_p;
	time_t		zero_time;
	int			is_died;
	pthread_t	death_monitor;
	t_mutex		*forks;
	t_mutex		death_mutex;
	t_mutex		print_mutex;
	t_mutex		eat_mutex;
}	t_data;

typedef struct s_philo
{
	size_t		id;
	time_t		last_time_eats;
	int			num_times_eats;	
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

int		init_data_struct(t_data *data, char **av);
int		init_philo_struct(t_philo *philosophers, t_data *data);
void	*routine(void *param);
void	clean_up(t_data *data, size_t i, int flag);
time_t	get_current_time(t_data *data);
time_t	get_zero_time(void);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
void	ft_usleep(time_t time, t_data *data);
void	write_log(t_philo *philo, char *message);
int		ft_atoi(const char *str);
void	*death_monitoring(void *philos);
void	get_set_last_eat(t_philo *philo, int flag, time_t *time, int *num_eat);
int		get_death(t_data *data);
int		detach_all_threads(t_philo *philosophers, t_data *data);

#endif