/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:18:52 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/17 07:52:06 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*philosopher(void *param);
static bool	all_philos_runnig(t_data *data);
static void	*monitor(void *param);
void		get_forks(t_philo *philo);
void		release_forks(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

void	dinner(t_data *data)
{
	int	i;

	if (data->philo_nbr > 1)
	{
		i = data->philo_nbr;
		while (--i >= 0)
			pthread_create(&data->philos[i].th_id, NULL, philosopher,
				&data->philos[i]);
		setter_long(&data->data_mtx, &data->start_time, get_time());
		pthread_create(&data->monitor, NULL, monitor, data);
		setter_bool(&data->data_mtx, &data->monitor_run, true);
		i = data->philo_nbr;
		while (--i >= 0)
			pthread_join(data->philos[i].th_id, NULL);
		setter_bool(&data->data_mtx, &data->philo_died, true);
		pthread_join(data->monitor, NULL);
	}
	else
		simulate_single_philosopher(data);
}

void	eat(t_philo *philo)
{
	get_forks(philo);
	setter_long(&philo->philo_mtx, &philo->last_eat_start_time, get_time());
	print_status(philo, EATING);
	increase_long(&philo->philo_mtx, &philo->eat_count);
	usleep(philo->data->eat_time);
	release_forks(philo);
	if (getter_long(&philo->philo_mtx, &philo->eat_count)
		== philo->data->max_meals)
		setter_bool(&philo->philo_mtx, &philo->full, true);
}

void	get_forks(t_philo *philo)
{
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

void	release_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&philo->own->mtx);
		pthread_mutex_unlock(&philo->additional->mtx);
	}
	else
	{
		pthread_mutex_unlock(&philo->additional->mtx);
		pthread_mutex_unlock(&philo->own->mtx);
	}
}

static void	*philosopher(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	while (!getter_bool(&philo->data->data_mtx, &philo->data->monitor_run))
		;
	setter_long(&philo->philo_mtx, &philo->last_eat_start_time,
		philo->data->start_time);
	increase_long(&philo->data->data_mtx, &philo->data->philos_running_cont);
	if (philo->index % 2 == 0 && philo->data->philo_nbr % 2 == 0)
		usleep(1000 * 3);
	while (!simulation_status(philo->data)
		&& !getter_bool(&philo->philo_mtx, &philo->full))
	{
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	usleep(philo->data->sleep_time);
}

void	thinking(t_philo *philo)
{
	long	tmp1;
	long	tmp2;

	print_status(philo, THINKING);
	if (philo->data->philo_nbr % 2 != 0 && philo->index % 2 != 0)
	{		
		tmp1 = (philo->data->eat_time * 2 - philo->data->sleep_time) * 0.30;
		tmp2 = philo->data->eat_time / 2;
		// printf("first: %li\n", tmp1);
		// printf("second: %li\n", tmp2);
		usleep(tmp1);
	}
}

static void	*monitor(void *param)
{
	t_data	*data;
	t_philo	*philo;
	int		i;
	long	time;
	long	time_to_die;

	data = (t_data *)param;
	time_to_die = data->die_time;
	while (!all_philos_runnig(data))
		;
	while (!getter_bool(&data->data_mtx, &data->philo_died))
	{
		i = data->philo_nbr;
		while (--i >= 0 && !getter_bool(&data->data_mtx, &data->philo_died))
		{
			philo = data->philos + i;
			if (getter_bool(&philo->philo_mtx, &philo->full))
				continue ;
			time = getter_long(&philo->philo_mtx, &philo->last_eat_start_time);
			if (get_time() - time > time_to_die)
			{
				setter_bool(&data->data_mtx, &data->philo_died, true);
				print_status(philo, DIED);
				return (NULL);
			}
		}
	}
	return (NULL);
}

static bool	all_philos_runnig(t_data *data)
{
	bool	tmp;

	pthread_mutex_lock(&data->data_mtx);
	tmp = (data->philos_running_cont == data->philo_nbr);
	pthread_mutex_unlock(&data->data_mtx);
	return (tmp);
}
