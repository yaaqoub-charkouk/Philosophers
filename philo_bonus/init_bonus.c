#include "philo_bonus.h"

int	init_data_struct(t_data *data, char **av)
{
	data->zero_time = get_zero_time();
	if (data->zero_time == 0)
			return (0);
	data->is_died = 0;
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
			data->max_eating_count_p = ft_atoi(av[5]);
	else
			data->max_eating_count_p = -2;
	if (data->num_of_philos == SIZE_T_MAX || data->time_to_die == -1
			|| data->time_to_eat == -1 || data->time_to_sleep == -1
			|| data->max_eating_count_p == -1)
			return (write(2, "Error\nInvalid argument", 22), 0);
	return (1);
}

int	create_philo_process(t_data *data, pidt *pid_s)
{
	int	i;

	i = 0;
	
}