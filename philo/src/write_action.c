#include <philo.h>

void	write_action(int id, long time, t_states state)
{
	char		*string;

	if (state == TAKEN_FORK)
		string = CYAN "has taken a fork" RESET "\n";
	else if (state == EATING)
		string = WHITE "is eating" RESET "\n";
	else if (state == SLEEPING)
		string = BLUE "is sleeping" RESET "\n";
	else if (state == THINKING)
		string = YELLOW "is thinking" RESET "\n";
	else if (state == DIED)
		string = RED "died" RESET "\n";
	printf("%-6li""%d"" %s", time, id, string);
}

long	get_time_since_init(t_data *data)
{
	long	time;

	time = get_time();
	return (time - data->start_time);
}

int	ft_strlen(char *s)
{
	char	*start;

	start = s;
	while (*s)
		s++;
	return (s - start);
}
