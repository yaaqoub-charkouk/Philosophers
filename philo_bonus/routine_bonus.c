/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:00:37 by ycharkou          #+#    #+#             */
/*   Updated: 2025/04/01 16:21:38 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_log(t_data *data, size_t id, char *log)
{
	sem_wait(data->print);
	printf("%zu %zu %s\n", get_current_time(data), id, log);
	sem_post(data->print);
}

void	take_forks(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	write_log(data, philo->id, "has taken a fork");
	sem_wait(data->forks);
	write_log(data, philo->id, "has taken a fork");
}

void	*death_monitoring(void	*parameter)
{
	t_philo	*philo;
	time_t	last_meal;
	int		num_eaten;
	
	philo = (t_philo *)parameter;
	while (1)
	{
		sem_wait(philo->data->death_sem);
		last_meal = philo->last_meal;
		num_eaten = philo->num_eaten;
		sem_post(philo->data->death_sem);		
		if (get_current_time(philo->data) - last_meal >= philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("\033[1;31m%zu %zu died\033[0m\n",
				get_current_time(philo->data), philo->id);
			exit(1);
		}
		if (philo->data->max_eating_count_p != -2 && num_eaten == philo->data->max_eating_count_p)
		{
			// usleep(philo->data->time_to_eat);
			// printf("%zu\n", philo->id);
			if (philo->id == philo->data->num_of_philos)			
				exit(1);
		}
		usleep(500);
	}
	return (NULL);
}


void	routine(t_data *data, t_philo *philo)
{
	pthread_t	death_monitor;

	pthread_create(&death_monitor, NULL, death_monitoring, philo);
	pthread_detach(death_monitor);
	if (data->num_of_philos == 1)
	{
		write_log(data, philo->id, "has taken a fork");
		usleep(data->time_to_eat * 1000);
		write_log(data, philo->id, "died");
		sem_post(data->is_died);
		exit(0);
	}
	while (1)
	{
		if (philo->num_eaten != philo->data->max_eating_count_p)
		{
			write_log(data, philo->id, "is thinking");
			take_forks(data, philo);
			write_log(data, philo->id, "is eating");
			
			// avoid data race 
			sem_wait(data->death_sem);
			philo->last_meal = get_current_time(data);
			sem_post(data->death_sem);
			
			usleep(data->time_to_eat * 1000); // time to eat
			
			sem_wait(data->death_sem);
			philo->num_eaten++;
			sem_post(data->death_sem);
					
			sem_post(data->forks);
			sem_post(data->forks);
			
			write_log(data, philo->id, "is sleeping");
			usleep(data->time_to_sleep * 1000); // time to sleep 
			write_log(data, philo->id, "is thinking");
		}
	}
	exit(0);
}
