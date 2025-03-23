#include "philo.h"



void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1) // change 0 to 1
	{
		pthread_mutex_lock(philo->right_fork);
		ft_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_printf(philo, "has taken a fork");
	}
	else
	{
		// usleep(10);
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
	ft_usleep(philo->data->time_to_eat , philo->data);
	// we add a mutex , to prevent from data race , writing and reading from the death thread 
	pthread_mutex_lock(&philo->philo_mutex);
	philo->num_times_eats++;
	philo->last_time_eats = get_current_time(philo->data); // offset time ;
	pthread_mutex_unlock(&philo->philo_mutex);
	// unlock the mutex so that other can do the same operation , in the death monitoring 
	release_fork(philo); // release mutex;
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