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
	t_fork	*forks;
	t_philo	*philos;

	forks = data->forks;
	philos = data->philos;
	i = data->fork_nbr;
	while (i)
		pthread_mutex_destroy(&forks[--i].mtx);
	i = data->philo_nbr;
	while (i)
		pthread_mutex_destroy(&philos[--i].philo_mtx);
	free(data->philos);
	free(data->forks);
}

void	simulate_single_philosopher(t_data *data)
{
	t_philo		*philo;

	philo = data->philos;
	pthread_mutex_lock(&philo->own->mtx);
	print_status(philo, TAKEN_FORK);
	usleep(data->die_time * 1000);
	print_status(philo, DIED);
	pthread_mutex_unlock(&philo->own->mtx);
}
