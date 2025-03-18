#include "philo.h"

void	take_left_fork_first(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("philosopher %d has taken the left fork",  philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("philosopher %d has taken the right fork", philo->id);
}
void	take_right_fork_first(t_philo	*philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("philosopher %d has taken the right fork", philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("philosopher %d has taken the left fork",  philo->id);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	printf("philosopher %d has released the left fork", philo->id);
	pthread_mutex_unlock(philo->left_fork);
	printf("philosopher %d has released the right fork", philo->id);
}

void	eat(t_philo *philo)
{
	// take_fork(philo); //lock mutex;
	if (philo->id % 2 == 0) // to avoid deadlock problem 
		take_left_fork_first(philo);
	else if (philo->id % 2 == 1)
	{
		usleep(15000); // just to give time for even philo , so that philosophers will not try to catch te same fork 
		take_right_fork_first(philo);
	}
	
	printf("philosopher %d has taken a fork", philo->id); // the film dayer ela how to take and release fork 
	printf("philosopher %d is eating", philo->id);
	philo->num_times_eats++;
	philo->last_time_eats = get_current_time(philo->data); // offset time ;
	usleep(philo->data->time_to_eat * 1000);
	release_fork(philo); // release mutex;
}

void	sleep(t_philo *philo)
{
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printf("%lld %d is thinking", get_current_time(philo->data), philo->id);
}