#include "philo.h"

void    last_eat(t_philo *philo, int flag, time_t *time, int *num_eat)
{
	pthread_mutex_lock(&philo->data->eat);
	if (flag == 1)
	{
		philo->last_time_eats = get_current_time(philo->data);
		philo->num_times_eats++;
	}
	else
	{
		*time = philo->last_time_eats;
		*num_eat = philo->num_times_eats;
	}
	pthread_mutex_unlock(&philo->data->eat);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_printf(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_printf(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	ft_printf(philo, "is eating");
	ft_usleep(philo->data->time_to_eat , philo->data); // check if died or not
	last_eat(philo, 1, 0, 0);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep , philo->data);
}

void	think(t_philo *philo)
{
	ft_printf(philo, "is thinking");
}