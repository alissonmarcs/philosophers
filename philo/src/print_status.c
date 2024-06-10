#include <philo.h>

void	print_status(t_philo *philo, t_status status)
{
	long		time;

	pthread_mutex_lock(&philo->data->print_mtx);
	time = get_time_since_init(philo->data);
	if (status == DIED && simulation_status(philo->data))
		printf("%-6li""%d"" %s\n", time, philo->index, RED "died" RESET);
	else if (status == TAKEN_FORK && !simulation_status(philo->data))
		printf("%-6li""%d"" %s\n", time, philo->index, CYAN "has taken a fork" RESET);
	else if (status == EATING && !simulation_status(philo->data))
		printf("%-6li""%d"" %s\n", time, philo->index, WHITE "is eating" RESET);
	else if (status == SLEEPING && !simulation_status(philo->data))
		printf("%-6li""%d"" %s\n", time, philo->index, BLUE "is sleeping" RESET);
	else if (status == THINKING && !simulation_status(philo->data))
		printf("%-6li""%d"" %s\n", time, philo->index, YELLOW "is thinking" RESET);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

long	get_time_since_init(t_data *data)
{
	return (get_time() - data->start_time);
}

bool	simulation_status(t_data *data)
{
	return (getter_bool(&data->data_mtx, &data->philo_died));
}
