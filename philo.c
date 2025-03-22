#include "philo.h"



/* routine:
	what each philo should do ;*/



int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philosophers; //array of philosophers

	if (ac == 5 || ac == 6)
	{
		if (!init_data_struct(&data, av))
			return (1);
		philosophers = malloc(data.num_of_philos * sizeof(t_philo));
		if (!philosophers)
			return(1);
		if (!init_philo_struct(philosophers, &data))
			return (1); // until this philosphers / threads are created and joined 
	}
	else
		printf("Error\n");
	return (0);
}
