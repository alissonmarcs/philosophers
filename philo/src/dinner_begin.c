#include <philo.h>

void	ft_get_fork(t_philo *philo);

void	*philosopher(void *param)
{
	t_philo *philo;

	philo = (t_philo *) param;
	while (true)
	{
		ft_get_fork(philo);
		write_action(philo, EATING);
		usleep(philo->data->eat_time);
		if (philo->last_eat_start_time == -1)
			philo->last_eat_start_time = get_time() - philo->data->start_time;
		else
			philo->last_eat_start_time = get_time() - philo->last_eat_start_time;
		if (philo->last_eat_start_time > philo->data->die_time)
		{
			write_action(philo, DIED);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->additional->mtx);
		pthread_mutex_unlock(&philo->own->mtx);
		write_action(philo, SLEEPING);
		usleep(philo->data->sleep_time);
		write_action(philo, THINKING);
	}
	return ((void *) 42);
}

void	ft_get_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->own->mtx);
		write_action(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->additional->mtx);
		write_action(philo, TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->additional->mtx);
		write_action(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->own->mtx);
		write_action(philo, TAKEN_FORK);
	}
}

void	dinner(t_data *data)
{
	t_philo		*current;
	int			i;

	i = data->philo_nbr - 1;
	while (i >= 0)
	{
		current = data->philos + i;
		pthread_create(&current->th, NULL, philosopher, current);
		i--;
	}
	i = data->philo_nbr - 1;
	while (i >= 0)
	{
		current = data->philos + i;
		pthread_join(current->th, NULL);
		i--;
	}
}
