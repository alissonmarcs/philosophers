/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:51:12 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/18 13:51:13 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	sleeping(t_philo *philo);
static void	thinking(t_philo *philo);

void	*philosopher(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (!get_bool(&philo->data->data_mtx, &philo->data->monitor_run))
		;
	set_long(&philo->philo_mtx, &philo->last_eat, philo->data->start_time);
	increase_long(&philo->data->data_mtx, &philo->data->philos_running_cont);
	if (philo->index % 2 == 0 && philo->data->philo_nbr % 2 == 0)
		usleep(1000 * 3);
	while (!simulation_status(philo->data) && !get_bool(&philo->philo_mtx,
			&philo->full))
	{
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

static void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEPING);
	usleep(philo->data->sleep_time);
}

static void	thinking(t_philo *philo)
{
	long	tmp1;
	long	tmp2;

	print_status(philo, THINKING);
	if (philo->data->philo_nbr % 2 != 0 && philo->index % 2 != 0)
	{
		tmp1 = (philo->data->eat_time * 2 - philo->data->sleep_time) * 0.42;
		tmp2 = philo->data->eat_time / 2;
		usleep(tmp1);
	}
}
