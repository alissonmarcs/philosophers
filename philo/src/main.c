#include <philo.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_argv(argc, argv))
		return (EXIT_FAILURE);
	init_data(&data, argv);
	debug(&data);
	clear(&data);
	return (42);
}
