/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:18:52 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/18 13:50:52 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*monitor(void *param);
static bool	is_all_running(t_data *data);
static void	wait_philosophers(t_data *data);

void	dinner(t_data *data)
{
	int	i;

	if (data->philo_nbr > 1)
	{
		i = data->philo_nbr;
		while (--i >= 0)
			pthread_create(&data->philos[i].th_id, NULL, philosopher,
				&data->philos[i]);
		set_long(&data->data_mtx, &data->start_time, get_time());
		pthread_create(&data->monitor, NULL, monitor, data);
		set_bool(&data->data_mtx, &data->monitor_run, true);
		i = data->philo_nbr;
		while (--i >= 0)
			pthread_join(data->philos[i].th_id, NULL);
		set_bool(&data->data_mtx, &data->philo_died, true);
		pthread_join(data->monitor, NULL);
	}
	else
		simulate_single_philosopher(data);
}

static void	*monitor(void *param)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)param;
	wait_philosophers(data);
	i = data->philo_nbr;
	while (--i >= 0)
	{
		philo = &data->philos[i];
		if (get_bool(&philo->philo_mtx, &philo->full))
			continue ;
		if (simulation_status(data))
			break ;
		if (get_time() - get_long(&philo->philo_mtx,
				&philo->last_eat) > data->die_time)
		{
			set_bool(&data->data_mtx, &data->philo_died, true);
			print_status(philo, DIED, DEBUG_MODE);
			break ;
		}
		if (i == 0)
			i = data->philo_nbr;
	}
	return (NULL);
}

static void	wait_philosophers(t_data *data)
{
	while (!is_all_running(data))
		;
}

static bool	is_all_running(t_data *data)
{
	bool	tmp;

	pthread_mutex_lock(&data->data_mtx);
	tmp = (data->philos_running_cont == data->philo_nbr);
	pthread_mutex_unlock(&data->data_mtx);
	return (tmp);
}
