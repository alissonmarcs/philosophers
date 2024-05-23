#include <philo.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_argv(argc, argv))
		return (EXIT_FAILURE);
	init_data(&data, argv);
	pthread_create(&data.philos[0].th, NULL, philosopher, data.philos);
	pthread_create(&data.philos[1].th, NULL, philosoph er, data.philos + 1);
	pthread_join(data.philos[0].th, NULL);
	pthread_join(data.philos[1].th, NULL);
	clear(&data);
	return (42);
}
