#include <philo.h>

void	debug(t_data *data)
{
	int			i;
	t_philo		*current;

	i = -1;
	printf("\n\n\t\t---- DEBUG MODE ----\n\n\n");
	while (++i < data->philo_nbr)
	{
		current = data->philos + i;
		printf("\t\tPhilo id: %d\n", current->id);
		printf("\t\tOwn fork: %p\n", current->own);
		if (current->own)
			printf("\t\t\tOwn fork id: %d\n", current->own->id);
		printf("\t\tAdditional fork: %p\n", current->additional);
		if (current->additional)
			printf("\t\t\tOwn fork id: %d\n", current->additional->id);
		printf("\n\t\t\t---\n\n");
	}
}
