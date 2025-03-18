#include "philo.h"
#include <sys/time.h>

int	is_died(t_philo *philo)
{
	int	i;

	i = 0;
	while(i < philo->data->num_of_philos)
	{
		if (philo[i].data->is_died)
			return (1);
		if ((get_current_time(philo[i].data) - philo[i].last_time_eats) > philo[i].data->time_to_die)
		{
			printf("%lld %d died", get_current_time(philo[i].data), philo[i].id);
			philo[i].data->is_died = 1;
			return (1);
		}
		i++;
		usleep(500);
	}
	return (0);
}

void	*routine(void *param)
{
	t_philo *philosopher;

	philosopher = (t_philo *)param;
	while (!philosopher->data->is_died)
	{
		eat(philosopher);
		sleep(philosopher);
		think(philosopher);
		if (is_died(philosopher))
			break ;
	}
	return (NULL);
}
