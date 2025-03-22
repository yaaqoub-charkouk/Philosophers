#include "philo.h"

// void	take_left_fork_first(t_philo	*philo)
// {
// 	pthread_mutex_lock(philo->left_fork);
// 	// printf("%zu %zu has taken the left fork\n", get_current_time(philo->data), philo->id);
// 	pthread_mutex_lock(philo->right_fork);
// 	// printf("%zu %zu has taken the right fork\n", get_current_time(philo->data), philo->id);
// 	printf("%zu %zu has taken a fork\n", get_current_time(philo->data), philo->id); // the film dayer ela how to take and release fork 
// }
// void	take_right_fork_first(t_philo	*philo)
// {
// 	pthread_mutex_lock(philo->right_fork);
// 	// printf("%zu %zu has taken the right fork\n", get_current_time(philo->data), philo->id);
// 	pthread_mutex_lock(philo->left_fork);
// 	// printf("%zu %zu has taken the left fork\n",  get_current_time(philo->data), philo->id);
// 	printf("%zu %zu has taken a fork\n", get_current_time(philo->data), philo->id); // the film dayer ela how to take and release fork 
// }

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	// printf("%zu %zu has released the left fork\n", get_current_time(philo->data), philo->id);
	pthread_mutex_unlock(philo->right_fork);
	// printf("%zu %zu has released the right fork\n", get_current_time(philo->data), philo->id);
	// printf("philosopher %zu has released the fork\n", philo->id);

}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		// printf("%zu %zu has taken the left fork\n", get_current_time(philo->data), philo->id);
		ft_printf(philo, "has taken a fork"); // the film dayer ela how to take and release fork 
		pthread_mutex_lock(philo->left_fork);
		// printf("%zu %zu has taken the right fork\n", get_current_time(philo->data), philo->id);
		ft_printf(philo, "has taken a fork");
		// printf("%zu %zu has taken a fork\n", get_current_time(philo->data), philo->id); // the film dayer ela how to take and release fork 
	}
	else
	{
		// ft_usleep(10);
		pthread_mutex_lock(philo->left_fork);
		ft_printf(philo, "has taken a fork");
		// printf("%zu %zu has taken the left fork\n", get_current_time(philo->data), philo->id);
		// printf("%zu %zu has taken a fork\n", get_current_time(philo->data), philo->id); // the film dayer ela how to take and release fork 
		pthread_mutex_lock(philo->right_fork);
		ft_printf(philo, "has taken a fork");
		// printf("%zu %zu has taken the right fork\n", get_current_time(philo->data), philo->id);
		// printf("%zu %zu has taken a fork\n", get_current_time(philo->data), philo->id); // the film dayer ela how to take and release fork 
	}
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	ft_printf(philo, "is eating");
	ft_usleep(philo->data->time_to_eat , philo->data);
	philo->num_times_eats++;
	philo->last_time_eats = get_current_time(philo->data); // offset time ;
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