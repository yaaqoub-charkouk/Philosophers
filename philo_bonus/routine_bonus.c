/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycharkou <ycharkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:00:37 by ycharkou          #+#    #+#             */
/*   Updated: 2025/04/06 08:32:44 by ycharkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	write_log(data, philo->id, "has taken a fork");
	sem_wait(data->forks);
	write_log(data, philo->id, "has taken a fork");
}

void	helper_set(t_philo *philo, time_t	*last_meal, int	*num_eaten)
{
	sem_wait(philo->data->death_sem);
	*last_meal = philo->last_meal;
	*num_eaten = philo->num_eaten;
	sem_post(philo->data->death_sem);
}

void	*death_monitoring(void	*parameter)
{
	t_philo	*philo;
	time_t	last_meal;
	int		num_eaten;
	
	philo = (t_philo *)parameter;
	while (1)
	{
		helper_set(philo, &last_meal, &num_eaten);
		if (get_current_time(philo->data) - last_meal 
			>= philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("\033[1;31m%zu %zu died\033[0m\n",
				get_current_time(philo->data), philo->id);
			exit(1);
		}
		if (philo->data->max_eating_count_p != -2 
			&& num_eaten == philo->data->max_eating_count_p
			&& philo->id == philo->data->num_of_philos)
			exit(1);
		usleep(500);
	}
	return (NULL);
}

void	eat(t_data *data, t_philo *philo)
{
	write_log(data, philo->id, "is thinking");
	take_forks(data, philo);
	write_log(data, philo->id, "is eating");
	sem_wait(data->death_sem);
	philo->last_meal = get_current_time(data);
	sem_post(data->death_sem);
	ft_usleep(data->time_to_eat);
	sem_wait(data->death_sem);
	philo->num_eaten++;
	sem_post(data->death_sem);
	sem_post(data->forks);
	sem_post(data->forks);
	write_log(data, philo->id, "is sleeping");
	ft_usleep(data->time_to_sleep);
	write_log(data, philo->id, "is thinking");
}

void	routine(t_data *data, t_philo *philo)
{
	pthread_t	death_monitor;

	if (data->num_of_philos == 1)
	{
		write_log(data, philo->id, "has taken a fork");
		usleep(data->time_to_die * 1000);
		printf("\033[1;31m%zu %zu died\033[0m\n",
			get_current_time(philo->data), philo->id);
		exit(0);
	}
	pthread_create(&death_monitor, NULL, death_monitoring, philo);
	pthread_detach(death_monitor);
	while (1)
	{
		if (philo->num_eaten != philo->data->max_eating_count_p)
			eat(data, philo);

		// test 
		// if (philo->num_eaten == philo->data->max_eating_count_p)
		// 	exit(0);
	}
	exit(0);
}
