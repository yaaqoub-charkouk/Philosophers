#include "philo.h"



/* routine:
	what each philo should do ;*/



int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers; //array of philosophers

	if (ac == 4 || ac == 5)
	{
		init_data_struct(&data, av);
		philosophers = malloc(data.num_of_philos * sizeof(t_philo));
		if (!philosophers)
			return(1);
		init_philo_struct(philosophers, data);
	}
	else
		printf("Error\n");
}
