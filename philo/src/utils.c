#include <philo.h>

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	ft_atol(const char *str)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		sign = 1 - 2 * (*str++ == '-');
	while (*str >= '0' && *str <= '9')
		result = 10 * result + (*str++ - '0');
	return (result * sign);
}

void	clear(t_data *data)
{
	int		i;
	t_fork	*current;

	current = data->forks;
	i = data->fork_nbr;
	while (i)
		pthread_mutex_destroy(&current[--i].mtx);
	free(data->philos);
	free(data->forks);
}
