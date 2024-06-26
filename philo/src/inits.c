/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:19:03 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/17 07:19:05 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_forks(t_data *data);
static void	init_philos(t_data *data);
static void	save_argv(t_data *data, char **argv);
static void	assign_forks(t_data *data);

void	init_data(t_data *data, char **argv)
{
	pthread_mutex_init(&data->data_mtx, NULL);
	pthread_mutex_lock(&data->data_mtx);
	save_argv(data, argv);
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = malloc(sizeof(t_fork) * data->fork_nbr);
	data->start_time_set = false;
	data->philo_died = false;
	init_forks(data);
	assign_forks(data);
	pthread_mutex_init(&data->print_mtx, NULL);
	data->philos_running_cont = 0;
	init_philos(data);
	pthread_mutex_unlock(&data->data_mtx);
}

static void	assign_forks(t_data *data)
{
	int		i;
	t_philo	*current_philo;
	t_fork	*current_fork;

	i = data->fork_nbr;
	while (--i >= 0)
	{
		current_philo = data->philos + i;
		current_fork = data->forks + i;
		current_philo->own = current_fork;
		if (i == 0)
			current_philo->additional = current_fork + (data->philo_nbr - 1);
		else
			current_philo->additional = current_fork - 1;
	}
}

static void	init_forks(t_data *data)
{
	int		i;
	t_fork	*current;

	i = -1;
	while (++i < data->fork_nbr)
	{
		current = data->forks + i;
		current->id = i + 1;
		pthread_mutex_init(&current->mtx, NULL);
	}
}

static void	save_argv(t_data *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->fork_nbr = data->philo_nbr;
	data->die_time = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]) * 1000;
	data->sleep_time = ft_atol(argv[4]) * 1000;
	if (argv[5])
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
}

static void	init_philos(t_data *data)
{
	int		i;
	t_philo	*current;

	i = -1;
	while (++i < data->philo_nbr)
	{
		current = data->philos + i;
		current->index = i + 1;
		current->data = data;
		current->eat_count = 0;
		current->full = false;
		pthread_mutex_init(&current->philo_mtx, NULL);
	}
}
