#include <philo.h>

void	*philosopher(void *param)
{
	t_philo *philo;

	philo = (t_philo *) param;
	while (!getter_bool(&philo->data->data_mtx, &philo->data->monitor_run))
		;
	increase_long(&philo->data->data_mtx, &philo->data->philos_running_cont);
	while (true)
	{
		if (getter_bool(&philo->data->data_mtx, &philo->data->philo_died))
			return (NULL);
		get_forks(philo);
		philo->eat_count++;
		setter_long(&philo->philo_mtx, &philo->last_eat_start_time, get_time());
		print_status(philo, EATING);
		usleep(philo->data->eat_time);
		pthread_mutex_unlock(&philo->additional->mtx);
		pthread_mutex_unlock(&philo->own->mtx);
		if (philo->eat_count == philo->data->max_meals)
		{
			setter_bool(&philo->philo_mtx, &philo->full, true);
			break ;
		}
		print_status(philo, SLEEPING);
		usleep(philo->data->sleep_time);
		print_status(philo, THINKING);
		if (philo->data->philo_nbr % 2 != 0 && philo->index % 2 != 0)
			usleep(500);
	}
	return (NULL);
}

void	get_forks(t_philo *philo)
{
	if (getter_bool(&philo->data->data_mtx, &philo->data->philo_died))
		return ;
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->own->mtx);
		print_status(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->additional->mtx);
		print_status(philo, TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->additional->mtx);
		print_status(philo, TAKEN_FORK);
		pthread_mutex_lock(&philo->own->mtx);
		print_status(philo, TAKEN_FORK);
	}
}

bool	all_philos_runnig(t_data *data)
{
	bool	tmp;

	pthread_mutex_lock(&data->data_mtx);
	tmp = (data->philos_running_cont == data->philo_nbr);
	pthread_mutex_unlock(&data->data_mtx);
	return (tmp);
}

void	*monitor(void *param)
{
	t_data	*data;
	t_philo	*philo;
	int		i;
	long	time;
	long	time_to_die;

	data = (t_data *) param;
	time_to_die = data->die_time;
	while (!all_philos_runnig(data))
		;
	while (!getter_bool(&data->data_mtx, &data->philo_died))
	{
		i = data->philo_nbr;
		while (--i >= 0 && !getter_bool(&data->data_mtx, &data->philo_died))
		{
			philo = data->philos + i;
			time = getter_long(&philo->philo_mtx, &philo->last_eat_start_time);
			if (!getter_bool(&philo->philo_mtx, &philo->full) && get_time() - time > time_to_die)
			{
				setter_bool(&data->data_mtx, &data->philo_died, true);
				print_status(philo, DIED);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	dinner(t_data *data)
{
	t_philo		*current;
	int			i;

	i = data->philo_nbr - 1;
	while (i >= 0)
	{
		current = data->philos + i;
		pthread_create(&current->th_id, NULL, philosopher, current);
		i--;
	}
	pthread_create(&data->monitor, NULL, monitor, data);
	setter_bool(&data->data_mtx, &data->monitor_run, true);
	i = data->philo_nbr - 1;
	while (i >= 0)
	{
		current = data->philos + i;
		pthread_join(current->th_id, NULL);
		i--;
	}
	setter_bool(&data->data_mtx, &data->philo_died, true);
	pthread_join(data->monitor, NULL);
}
