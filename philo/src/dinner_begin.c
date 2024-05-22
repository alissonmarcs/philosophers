#include <philo.h>

void	*philosopher(void *param)
{
	t_philo *philo;

	philo = (t_philo *) param;
	philo->last_eat_start_time = get_time();
	if (philo->id == 2)
	{
		pthread_mutex_lock(&philo->own->mtx);
		write_action(philo->id, get_time_since_init(philo->data), TAKEN_FORK);
		pthread_mutex_lock(&philo->additional->mtx);
		write_action(philo->id, get_time_since_init(philo->data), TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->additional->mtx);
		write_action(philo->id, get_time_since_init(philo->data), TAKEN_FORK);
		pthread_mutex_lock(&philo->own->mtx);
		write_action(philo->id, get_time_since_init(philo->data), TAKEN_FORK);		
	}
	write_action(philo->id, get_time_since_init(philo->data), EATING);
	usleep(philo->data->eat_time);
	pthread_mutex_unlock(&philo->own->mtx);
	pthread_mutex_unlock(&philo->additional->mtx);
	write_action(philo->id, get_time_since_init(philo->data), SLEEPING);
	usleep(philo->data->sleep_time);
	return ((void *) 42);
}

// void	dinner_begin(t_data *data)
// {

// }