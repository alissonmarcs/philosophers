/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:49:41 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/18 13:49:47 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	get_forks(t_philo *philo);
static void	release_forks(t_philo *philo);

void	eat(t_philo *philo)
{
	get_forks(philo);
	set_long(&philo->philo_mtx, &philo->last_eat, get_time());
	print_status(philo, EATING, DEBUG_MODE);
	increase_long(&philo->philo_mtx, &philo->eat_count);
	usleep(philo->data->eat_time);
	release_forks(philo);
	if (get_long(&philo->philo_mtx,
			&philo->eat_count) == philo->data->max_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
}

static void	get_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->own->mtx);
		print_status(philo, TAKEN_OWN_FORK, DEBUG_MODE);
		pthread_mutex_lock(&philo->additional->mtx);
		print_status(philo, TAKEN_ADITTIONAL_FORK, DEBUG_MODE);
	}
	else
	{
		pthread_mutex_lock(&philo->additional->mtx);
		print_status(philo, TAKEN_ADITTIONAL_FORK, DEBUG_MODE);
		pthread_mutex_lock(&philo->own->mtx);
		print_status(philo, TAKEN_OWN_FORK, DEBUG_MODE);
	}
}

static void	release_forks(t_philo *philo)
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
