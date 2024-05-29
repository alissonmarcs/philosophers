#include <philo.h>

void	print_status(t_philo *philo, t_status status)
{
	char		*string;

	if (status == TAKEN_FORK)
		string = CYAN "has taken a fork" RESET "\n";
	else if (status == EATING)
		string = WHITE "is eating" RESET "\n";
	else if (status == SLEEPING)
		string = BLUE "is sleeping" RESET "\n";
	else if (status == THINKING)
		string = YELLOW "is thinking" RESET "\n";
	else if (status == DIED)
		string = RED "died" RESET "\n";
	else
		return ;
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%-6li""%d"" %s", get_time_since_init(philo->data), philo->index, string);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

long	get_time_since_init(t_data *data)
{
	return (get_time() - data->start_time);
}
