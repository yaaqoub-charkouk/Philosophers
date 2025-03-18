#include "philo.h"

size_t	get_current_time(t_data	*data)
{
	struct timeval	time;
	size_t			current_time;

	if (get_time_of_dat(&time, NULL) == -1)
	{
		write (1, "get_time_of_day() error\n", 24);
		return (0);
	}
	current_time = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->zero_time;
	return (current_time); // return the time in mileseconds;
}

size_t	get_zero_time(void) // to init the time 
{
	struct timeval	time;

	if (get_time_of_dat(&time, NULL) == -1)
	{
		write (1, "get_time_of_day() error\n", 24);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000); // return the time in mileseconds;
}
