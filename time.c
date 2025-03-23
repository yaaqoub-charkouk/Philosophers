#include "philo.h"

time_t	get_current_time(t_data	*data)
{
	struct timeval	time;
	size_t			current_time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write (1, "get_time_of_day() error\n", 24);
		return (0);
	}
	current_time = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->zero_time;
	return (current_time); // return the time in mileseconds;
}

time_t	get_zero_time(void) // to init the time 
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write (1, "get_time_of_day() error\n", 24);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000); // return the time in mileseconds;
}

void	ft_usleep(time_t time, t_data *data)
{
	time_t	start;

	start = get_zero_time();
	while (get_zero_time() - start < time)
	{
		if (!is_still_alive(data))
			break ;
		usleep(100);
	}
}