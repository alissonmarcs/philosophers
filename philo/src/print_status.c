/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almarcos <almarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:19:16 by almarcos          #+#    #+#             */
/*   Updated: 2024/06/17 07:19:31 by almarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	get_time_since_init(t_data *data)
{
	return (get_time() - data->start_time);
}

void	print_status_debug(t_philo *philo, t_status status, long elapsed)
{

	if (status == TAKEN_OWN_FORK && !simulation_status(philo->data))
		printf(CYAN "%-6li" "%d" " has taken the own fork [%d]\n" RESET, elapsed, philo->index, philo->own->id);
	else if (status == TAKEN_ADITTIONAL_FORK && !simulation_status(philo->data))
		printf(CYAN "%-6li" "%d" " has taken the additional fork [%d]\n" RESET, elapsed, philo->index, philo->additional->id);
	else if (status == EATING)
		printf(WHITE"%-6li" "%d" " eating [%li]\n" RESET, elapsed, philo->index, philo->eat_count);
	else if (status == SLEEPING && !simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", elapsed, philo->index,
			BLUE "is sleeping" RESET);
	else if (status == THINKING && !simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", elapsed, philo->index,
			YELLOW "is thinking" RESET);
	else if (status == DIED && simulation_status(philo->data))
		printf("%-6li" "%d" " %s\n", elapsed, philo->index, RED "died" RESET);
}

void	print_status(t_philo *philo, t_status status, bool debug)
{
	long	time;

	if (get_bool(&philo->philo_mtx, &philo->full))
		return ;
	pthread_mutex_lock(&philo->data->print_mtx);
	time = get_time_since_init(philo->data);
	if (debug)
		print_status_debug(philo, status, time);
	else
	{
		if (status == DIED && simulation_status(philo->data))
			printf("%-6li" "%d" " %s\n", time, philo->index, RED "died" RESET);
		else if (status == TAKEN_FORK && !simulation_status(philo->data))
			printf("%-6li" "%d" " %s\n", time, philo->index,
				CYAN "has taken a fork" RESET);
		else if (status == EATING && !simulation_status(philo->data))
			printf("%-6li" "%d" " %s\n", time, philo->index,
				WHITE "is eating" RESET);
		else if (status == SLEEPING && !simulation_status(philo->data))
			printf("%-6li" "%d" " %s\n", time, philo->index,
				BLUE "is sleeping" RESET);
		else if (status == THINKING && !simulation_status(philo->data))
			printf("%-6li" "%d" " %s\n", time, philo->index,
				YELLOW "is thinking" RESET);
	}
	pthread_mutex_unlock(&philo->data->print_mtx);
}
