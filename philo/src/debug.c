#include <philo.h>

void	debug(t_data *data)
{
	int			i;
	t_philo		*current;

	i = -1;
	printf("\n\n\t\t\t---- DEBUG MODE ----\n\n\n");
	while (++i < data->philo_nbr)
	{
		current = data->philos + i;
		printf("\t\tPhilo id: %d\n", current->index);
		printf("\t\tForks:\n");
		if (current->own)
			printf("\t\t\tOwn fork id: %d\n", current->own->id);
		if (current->additional)
			printf("\t\t\tAdditional fork id: %d\n", current->additional->id);
		printf("\n\t\t-----------------------------------\n\n");
	}
}
