#include "philo.h"

void	ft_printf(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->is_died)
		printf("%zu %zu %s\n", get_current_time(philo->data), philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*routine(void *param)
{
	t_philo *philosopher;

	philosopher = (t_philo *)param;
	while (!philosopher->data->is_died)
	{
		eat(philosopher);
		// if (philosopher->data->is_died)
		// 	break ;
		ft_sleep(philosopher);
		// if (philosopher->data->is_died)
		// 	break ;
		think(philosopher);
		// if (philosopher->data->is_died)
		// 	break ;
	}
	return (NULL);
}
